#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

void add(Node** head, int v) {
    Node* n = malloc(sizeof(Node));
    n->value = v;
    n->next = *head;
    *head = n;
}

int bfs_distance(Node* adj[], int n, int src, int dest) {
    int *vis = malloc(n * sizeof(int));
    int *par = malloc(n * sizeof(int));
    for(int i=0;i<n;i++)
        {
            vis[i] = 0;
            par[i] = -1;
        }

    int *q = malloc(n * sizeof(int));
    int f=0, r=0;
    q[r++] = src;
    vis[src] = 1;

    while(f < r) {
        int u = q[f++];
        for(Node* t = adj[u]; t; t=t->next) {
            int v = t->value;
            if(!vis[v]) {
                vis[v] = 1;
                par[v] = u;
                q[r++] = v;
                if(v == dest) break;
            }
        }
    }

    if(!vis[dest]) { free(vis); free(par); free(q); return -1; }

    int len = 0;
    for(int v = dest; v != -1; v = par[v]) len++;

    free(vis); free(par); free(q);
    return len - 1;
}

int count_components(Node* adj[], int n) {
    int *vis = calloc(n, sizeof(int));
    int *q = malloc(n * sizeof(int));
    int f, r, comp = 0;

    for(int i=0;i<n;i++) {
        if(!vis[i]) {
            comp++;
            f = r = 0;
            q[r++] = i;
            vis[i] = 1;

            while(f < r) {
                int u = q[f++];
                for(Node* t = adj[u]; t; t=t->next) {
                    int v = t->value;
                    if(!vis[v]) { vis[v]=1; q[r++] = v; }
                }
            }
        }
    }

    free(vis); free(q);
    return comp;
}

int main(int argc, char** argv) {
    if(argc < 3) return printf("Usage: %s input.txt expected.txt\n", argv[0]), 1;

    FILE* f = fopen(argv[1],"r"); if(!f) return printf("Erreur ouverture\n"),1;

    int n,m; fscanf(f,"%d %d",&n,&m);

    Node** adj = calloc(n, sizeof(Node*));
    for(int i=0,a,b;i<m;i++) {
        fscanf(f,"%d %d",&a,&b);
        add(&adj[a-1], b-1);
        add(&adj[b-1], a-1);
    }

    int A,J; fscanf(f,"%d %d",&A,&J);
    fclose(f);

    int comp = count_components(adj,n);
    int dist = bfs_distance(adj,n,A-1,J-1);

    FILE* g = fopen(argv[2],"r"); if(!g) return printf("Erreur expected\n"),1;
    int ec, ed; fscanf(g,"%d %d",&ec,&ed);
    fclose(g);

    if(comp==ec && dist==ed)
        printf("Test OK\n");
    else
        printf("Test FAIL (attendu %d %d, got %d %d)\n", ec, ed, comp, dist);

    for(int i=0;i<n;i++){
        Node* t = adj[i];
        while(t){ Node* tmp=t; t=t->next; free(tmp); }
    }
    free(adj);
    return 0;
}

