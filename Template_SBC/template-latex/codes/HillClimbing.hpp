int near(int origin)
{   
	int near;
	float min=10000,mini;
	for(int i=0; i<graph[origin].size();i++)
	{       
		float dist=distance(dots[i].first,dots[coord_fin].first,dots[i].second,dots[coord_fin].second); 
		if(grafo[origin][i]!=0 and dist<=min )
		{
			min=dist;
			mini=grafo[origin][i];
			near=i;	
		}
	}
	cost+=mini;
	dots_traveled.push_back(origin);
	visited[origin]=true;
	return near;
}

void hill_climbing(vector <vector<float>> grafo)
{	
	int origin;
    origin=coord_ini;
	while (origin!=coord_fin) 
	{
		if(visited[origin]==true)
			return;
		origin=near(origin);		
	}
	dots_traveled.push_back(origin);
}