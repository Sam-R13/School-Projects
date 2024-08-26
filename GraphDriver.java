
public class GraphDriver {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		// Create a graph object
//		GraphAdjMatrix graph = new GraphAdjMatrix();
		GraphAdjList graph = new GraphAdjList();

		// add vertices to the graph
		graph.addVertex(new Vertex('A'));
		graph.addVertex(new Vertex('B'));
		graph.addVertex(new Vertex('C'));
		graph.addVertex(new Vertex('D'));
		graph.addVertex(new Vertex('Z'));
		
		// Vertex count
		System.out.println("Vertex Count: " + graph.getNumberOfVertices());
		// Edge count
		System.out.println("Edge Count: " + graph.getNumberOfEdges());
		
		// add edges to the graph
		graph.addEdge(new Vertex('A'), new Vertex('B'));
		graph.addEdge(new Vertex('A'), new Vertex('D'));
		graph.addEdge(new Vertex('B'), new Vertex('D'));
		graph.addEdge(new Vertex('C'), new Vertex('D'));
		graph.addEdge(new Vertex('C'), new Vertex('B'));
		graph.addEdge(new Vertex('C'), new Vertex('B'));
		graph.addEdge(new Vertex('C'), new Vertex('B'));
		graph.addEdge(new Vertex('B'), new Vertex('C'));
		
		graph.addEdge(new Vertex('Z'), new Vertex('A'));
		graph.addEdge(new Vertex('Z'), new Vertex('B'));
		graph.addEdge(new Vertex('Z'), new Vertex('D'));

		// Let's print the graph
		System.out.println(graph);
		// Vertex count
		System.out.println("Vertex Count: " + graph.getNumberOfVertices());
		// Edge count
		System.out.println("Edge Count: " + graph.getNumberOfEdges());
		
		// remove a vertex
		System.out.println("\nRemoving A...");
		graph.removeVertex(new Vertex('A'));

		// Let's print the graph
		System.out.println(graph);
		// Vertex count
		System.out.println("Vertex Count: " + graph.getNumberOfVertices());
		// Edge count
		System.out.println("Edge Count: " + graph.getNumberOfEdges());

		
	}

}
