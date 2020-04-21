void BFS()
{
	vector<bool> visited(dots.size(), false); 
	list<int> queue;
	queue.push_back(coord_ini);
	int a;
	while(!queue.empty())
	{
		a=queue.front();
		queue.pop_front();

        for (int i=0;i<tree[a].size();i++) 
        {
        	if (!visited[i]) 
            {
            	visited[i]=true;
            	queue.push_back(i);
            	dots_traveled.push_back(i);
            }   
            if(i==coord_fin)
            	return;
        }    
	}
}
