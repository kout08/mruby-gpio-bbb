#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mruby.h"
#include "mruby/value.h"
#include "./set_bbbpin.h"
//i2c header
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "./i2c.h"
//Use read, write
#include <unistd.h>

static mrb_value 
f_gpio_pinmode(mrb_state *mrb, mrb_value self)
{
	char buf[100];
	mrb_int pin, dir;
	mrb_get_args(mrb, "ii", &pin, &dir);
	pin=set_bbbpin(pin);
	if( pin == -1 ){
		printf("Error pinNo.\n");
		return mrb_fixnum_value(-1);
	}

	if( dir == 1 ){  // output
		sprintf(buf, "echo %d > /sys/class/gpio/export", pin);
		if( system(buf) != 0 )
			return mrb_fixnum_value(-1);
		sprintf(buf, "echo out > /sys/class/gpio/gpio%d/direction", pin);
		if( system(buf) != 0 )
			return mrb_fixnum_value(-1);
	} else {         // input
		sprintf(buf, "echo %d > /sys/class/gpio/export", pin);
		if( system(buf) != 0 )
			return mrb_fixnum_value(-1);
		sprintf(buf, "echo in > /sys/class/gpio/gpio%d/direction", pin);
		if( system(buf) != 0 )
			return mrb_fixnum_value(-1);
	}

	return mrb_nil_value();
}

static mrb_value
f_gpio_dwrite(mrb_state *mrb, mrb_value self)
{
	char buf[100];
	mrb_int pin, value;
	mrb_get_args(mrb, "ii", &pin, &value);
	pin=set_bbbpin(pin);
	if( pin == -1 ){
		printf("Error pinNo.\n");
		return mrb_fixnum_value(-1);
	}

	sprintf(buf, "echo %d > /sys/class/gpio/gpio%d/value", value, pin);
	if( system(buf) != 0 )
		return mrb_fixnum_value(-1);

	return mrb_nil_value();
}

static mrb_value
f_gpio_dread(mrb_state *mrb, mrb_value self)
{
	mrb_int pin,value;
	char buf[100], chval[10];
	FILE *fval;
	mrb_get_args(mrb, "i", &pin);

	sprintf(buf, "cat /sys/class/gpio/gpio%d/value", pin);
	fval=popen(buf,"r");
	if(fgets(chval,sizeof(chval),fval) == NULL)
		return mrb_fixnum_value(-1);
	pclose(fval);

	if( strcmp(chval,"0\n") == 0 ){
		value=0;
	} else if( strcmp(chval,"1\n") == 0 ){
		value=1;
	} else {	//error
		printf("Error digitalRead\n");
		return mrb_fixnum_value(-1);
	}
	return mrb_fixnum_value(value);
}

static mrb_value
f_gpio_isetup(mrb_state *mrb, mrb_value self)
{
	mrb_int devId, ret;
	mrb_get_args(mrb, "i", &devId);
	ret = i2cSetup(devId);

	return mrb_fixnum_value(ret);
}

static mrb_value
f_gpio_iwrite(mrb_state *mrb, mrb_value self)
{
	mrb_int fd, reg, data, ret;
	mrb_get_args(mrb, "iii", &fd, &reg, &data);
	ret = i2cWrite(fd, reg, data);

	return mrb_fixnum_value(ret);
}

static mrb_value
f_gpio_iread(mrb_state *mrb, mrb_value self)
{
	mrb_int fd, reg, ret;
	mrb_get_args(mrb, "ii", &fd, &reg);
	ret = i2cRead(fd, reg);

	return mrb_fixnum_value(ret);
}

static mrb_value
f_gpio_stdread(mrb_state *mrb, mrb_value self)
{
	mrb_int fd, bsize, ret;
	mrb_get_args(mrb, "ii", &fd, &bsize);
	ret = stdRead(fd, bsize);

	return mrb_fixnum_value(ret);
}

void
mrb_mruby_gpio_bbb_gem_init(mrb_state* mrb)
{
	struct RClass *c;
	c = mrb_define_module(mrb, "Gpio");

	mrb_define_const(mrb, c, "OUTPUT", mrb_fixnum_value(1));
	mrb_define_const(mrb, c, "INPUT", mrb_fixnum_value(0));
	mrb_define_const(mrb, c, "HIGH", mrb_fixnum_value(1));
	mrb_define_const(mrb, c, "LOW", mrb_fixnum_value(0));

	mrb_define_module_function(mrb, c, "pinMode", f_gpio_pinmode, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, c, "digitalWrite", f_gpio_dwrite, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, c, "digitalRead", f_gpio_dread, MRB_ARGS_REQ(1));
	
	//i2c
	mrb_define_module_function(mrb, c, "i2cSetup", f_gpio_isetup, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, c, "i2cWrite", f_gpio_iwrite, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, c, "i2cRead", f_gpio_iread, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, c, "stdRead", f_gpio_stdread, MRB_ARGS_REQ(2));
}

	void
mrb_mruby_gpio_bbb_gem_final(mrb_state* mrb)
{
}
