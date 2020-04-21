void DFS()
{	
	vector<bool> visited(dots.size(), false); 
	stack<int> stack;
	stack.push(coord_ini);
	int a;
	while(!stack.empty() and a!=coord_fin)
	{
		a=stack.top();
		stack.pop();
		if (!visited[a]) 
        { 
			dots_traveled.push_back(a);
            visited[a] = true; 
        } 
        for (int i=0;i<tree[a].size();i++) 
            if (!visited[i]) 
                stack.push(i); 
	}
}