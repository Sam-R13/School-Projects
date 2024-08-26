
public class GraphAdjMatrix {
	

	
	public GraphAdjMatrix() {
		// TODO Auto-generated constructor stub

		}
	
	public boolean addVertex(Vertex v) {

	}
	
	public boolean removeVertex(Vertex v) {

	}
	
	public boolean addEdge(Vertex u, Vertex v) {

	}
	
	public boolean removeEdge(Vertex u, Vertex v) {

	}
	
	public String toString() {
		String str = "";
		
		for(int i = 0; i < MAX_VERTEX; i++) {
			if(vertices[i] != null) {
				str += vertices[i].label;
				for(int j = 0; j < MAX_VERTEX; j++) {
					if(adjMatrix[i][j] != 0)
						str += "->" + vertices[j].label;
				}
				str += "\n";
			}
		}
			
		return str;
	}
	
	public int getNumberOfVertices() {
		return numberOfVertices;
	}

	public int getNumberOfEdges() {
		return numberOfEdges;
	}
}
