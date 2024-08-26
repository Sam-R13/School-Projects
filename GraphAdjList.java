import java.util.ArrayList;
import java.util.Iterator;

public class GraphAdjList {

	
	public GraphAdjList() {
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
		
		for(ArrayList<Vertex> list : adjList) {
			if(list.size()>0) {
				str += (char)(adjList.indexOf(list) + 'A');
				for(Vertex vertex: list) {
					str += "->" + vertex.label;
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
