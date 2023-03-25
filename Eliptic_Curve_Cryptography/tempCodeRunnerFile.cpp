 Point GeneratePointG(Entity E,ElipticCurve EC)
 {
 	srand(time(0));
	long long int x = rand()%EC.GetRangeC()+1;
	long long int y=E.FindY(EC.CalcYsqrt(x));	
	while(y==0 && x<EC.GetRangeC())
	{
		y=E.FindY(EC.CalcYsqrt(++x));	
	}
 	Point G(x,y);
 	return G;
 }