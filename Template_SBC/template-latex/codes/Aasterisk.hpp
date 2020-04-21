int near_a(int origin)
{   
	int near;
	float min=10000,mini;
	for(int i=0; i<graph[origin].size();i++)
	{       
		float dist=distance(dots[i].first,dots[coord_fin].first,dots[i].second,dots[coord_fin].second); 
		if(grafo[origin][i]!=0 and dist+grafo[origin][i]<=min )
		{
			min=dist+grafo[origin][i];
			mini=grafo[origin][i];
			near=i;	
		}
	}
	cost+=mini;
	dots_traveled.push_back(origin);
	visited[origin]=true;
	return near;
}

void a_aterisk(vector <vector<float>> grafo)
{	
	int origin;
    origin=coord_ini;
	while (origin!=coord_fin) 
	{
		if(visited[origin]==true)
			return;
		origin=near_a(origin);		
	}
	dots_traveled.push_back(origin);
}