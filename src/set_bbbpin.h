int set_bbbpin(int pin)
{
	switch(pin){
		case 0:
			return 30;
		case 1:
			return 60;
		case 2:
			return 31;
		case 3:
			return 50;
		case 4:
			return 48;
		case 5:
			return 51;
		case 6:
			return 3;
		case 7:
			return 2;
		case 8:
			return 49;
		case 9:
			return 15;
		case 10:
			return 14;
		case 11:
			return 16;
		case 12:
			return 112;
		case 13:
			return 20;
		case 14:
			return 7;
		default:
			return -1;
	}
}