int swap_add(int* xp, int *yp){
	int x = *xp;
	int y = *yp;
	*xp = y;
	*yp = x;
	return x+y;
}
int caller(){
	int arg1 = 222;
	int arg2 = 333;
	int sum = swap_add(&arg1, &arg2);
	int diff = arg1 - arg2;
	return sum*diff;
}