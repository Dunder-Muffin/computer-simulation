#include <vector>
#include <iostream>
#include <ctime>
using namespace std;
float time1, time2;
float CLK_TCK;
vector < vector<int> > g, gr;
vector<bool> used;
vector<int> order, component;  //TODO: add exeptions
 
void dfs1 (int v) {
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!used[g[v][i]])
			dfs1 (g[v][i]);
	order.push_back (v);
}
 
void dfs2 (int v) {
	used[v] = true;
	component.push_back (v);
	for (size_t i=0; i<gr[v].size(); ++i)
		if (!used[ gr[v][i] ])
			dfs2 (gr[v][i]);
}
 
int main() {
	time1 = clock();
	int n, m, num = 0;
	cout << "Put graph. First input means amount of vertex and arcs and then\
	you put arc by putting 2 connected vertex" << endl;
    cin >> n >> m;
    g.resize(n);
    gr.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back (b);
		gr[b].push_back (a);
	}
 
	used.assign (n, false);
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs1 (i);
    cout << "Graph:";
    for (int i : order)
    {
        cout << i << " ";
    }
    
    cout << endl;

	used.assign (n, false);
	for (int i=0; i<n; ++i) {
		int v = order[n-1-i];
		if (!used[v]) {
            num++;
			dfs2 (v);
            cout << "Strong coherence component #" << num << "\t";
			for (int j: component)
            {
                cout << j;
                if (j != component.back())
                    cout << ", ";
            }
            cout << endl;
			component.clear();
		}
	}
	time2 = clock();
	cout<<"Time: " << (time2-time1)/CLOCKS_PER_SEC<<endl;

    return 0;
}
