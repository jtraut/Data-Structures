import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;
import java.util.Stack;
import java.util.Deque;
import java.util.ArrayDeque;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;

// Note** Uploaded from moodle complete (4/30 before lecture); commented through for comprehension 
// not expecting extra credit for Prim and Dijkstras


class FestivalOfGraphs
{
	private Graph g;
	private ArrayList<String> names;
	private ArrayList<Double> lats;
	private ArrayList<Double> longs;
	
	public void init(String graphFile) 
	{
		System.out.println(graphFile);
		// open the file
		BufferedReader br = null;
		
		try
		{
			// open the file called "graph.txt"
			br = new BufferedReader(new FileReader(graphFile));
		
			// read the first line
			String line = br.readLine();	
			
			// convert the first line (a string) to an integer (numberOfVertices)
			Integer n = Integer.parseInt(line);
			
			g = new Graph(n);
		
			for (int fromVertex = 0; fromVertex < n; ++fromVertex)
			{
				line = br.readLine();
				if (line.length() > 0)
				{
					int pos = 0;
					while (line.indexOf("{", pos) > -1)
					{
						String sub = line.substring(line.indexOf("{", pos) + 1, line.indexOf("}", pos + 1));
						Integer toVertex = Integer.parseInt(sub.substring(0, sub.indexOf(",")));
						Integer weightOfEdge = Integer.parseInt(sub.substring(sub.indexOf(",") + 1, sub.length()));
						pos = line.indexOf("}", pos + 1);
						if (!g.hasEdge(fromVertex, toVertex))
							g.addEdge(fromVertex, toVertex, weightOfEdge);
					}	
				}	
			}
			g.printAdjacencyMatrix();
			System.out.println(DepthFirstList(0));
			System.out.println(BreadthFirstList(0));
		}
		catch (FileNotFoundException ex) {
			// handle FileNotFoundException
			System.out.println("No such file as " + graphFile + " in your directory");
		}
		catch (IOException ex) {
			// handle IOException
			System.out.println("Ran into problems processing " + graphFile);
		}
		finally {
			if (br != null) {
				try {
					br.close();
				}
				catch (IOException ex) {
					// handle IOException
					System.out.println("Ran into unrecoverable problems processing " + graphFile);
				}
			}
		}
		
	}
	
	public Graph PrimsAlgorithm(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		List<Integer> visited = new ArrayList<Integer>();
		for (int i = 0; i < g.getNumVertices(); ++i)
			visited.add(0);
		visited.set(v, 1);
		do
		{
			boolean initialMin = false;
			Integer cheapestEdge = 0;
			Integer cheapestFromVertex = v;
			Integer cheapestToVertex = v;
			Integer w;
			for (w = 0; w < g.getNumVertices(); ++w)
			{
				if (visited.get(w) == 1)
				{
					for (Integer x = 0; x < g.getNumVertices(); ++x)
					{
						if (g.hasEdge(w, x) && visited.get(x) == 0)
						{
							if (initialMin == false)
							{
								cheapestEdge = g.getAdjList(w).get(x);
								cheapestToVertex = x;
								cheapestFromVertex = w;
								initialMin = true;
							}
							else
								if (cheapestEdge > g.getAdjList(w).get(x))
								{
									cheapestEdge = g.getAdjList(w).get(x);
									cheapestToVertex = x;
									cheapestFromVertex = w;
								}
							System.out.println("Set " + cheapestFromVertex + " - " + cheapestToVertex + " " + cheapestEdge);
							
						}
					}
				}
			}
			System.out.println("Final " + cheapestFromVertex + " - " + cheapestToVertex + " " + cheapestEdge);
			if (cheapestEdge != 0 && cheapestFromVertex < g.getNumVertices() && cheapestToVertex != g.getNumVertices())
			{
				System.out.println("Adding to tree");
				t.addEdge(cheapestFromVertex, cheapestToVertex, cheapestEdge);
				visited.set(cheapestToVertex, 1);
			}
		} while (visited.contains(0));
		t.printAdjacencyMatrix();
		return t;
	}
	
	public List<Integer> DepthFirstList(Integer v)
	{
		List<Integer> vertices = new ArrayList<Integer>();
		// your "stack"
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		
		// Fill the visited list full of zeroes
		for (int i = 0; i < g.getNumVertices(); ++i)
			visited.add(0);
			
		// Insert vertex at the front of the deque
		toExplore.addFirst(v);
		
		// Replace element at space v with 1
		visited.set(v, 1);
		
		Integer w;  //local variable cashed; declared once 
		// Check if there are more vertices to look at
		while (toExplore.size() > 0)
		{
			// take the first vertex from the list
			w = toExplore.removeFirst();
			
			// add to the list of vertices
			vertices.add(w);
			
			// look through w's adjacency list 
			for (Integer x: g.getAdjList(w).keySet())
			{
				// if x has not yet been visited 
				if (visited.get(x) == 0)
				{
					// add x to the FRONT of our toExplore list 
					toExplore.addFirst(x);
					// mark x as visited 
					visited.set(x, 1);
				}
			}
		}
		return vertices;
	}
	
	public List<Integer> BreadthFirstList(Integer v) 
	{
		List<Integer> vertices = new ArrayList<Integer>();
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		for (int i = 0; i < g.getNumVertices(); ++i)
			visited.add(0);
		toExplore.addLast(v);
		visited.set(v, 1);
		Integer w;
		while (toExplore.size() > 0)
		{
			w = toExplore.removeFirst();
			vertices.add(w);
			for (Integer x: g.getAdjList(w).keySet())
			{
				if (visited.get(x) == 0)
				{
					toExplore.addLast(x); // main difference from depth
					visited.set(x, 1);
				}
			}
		}
		return vertices;
	}

	
	public Graph DepthFirstSpanningTree(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		for (int i = 0; i < g.getNumVertices(); ++i)
			visited.add(0);
		toExplore.addFirst(v); 
		Integer w;
		while (toExplore.size() > 0)
		{
			w = toExplore.removeFirst();
			for (Integer x: g.getAdjList(w).keySet())
			{
				if (visited.get(x) == 0)
				{
					t.addEdge(w, x, g.getAdjList(w).get(x));
					toExplore.addFirst(x);  //depth adds to front
					visited.set(x, 1);
				}
			}
		}
		return t;
	}
	
	
	public Graph BreadthFirstSpanningTree(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		for (int i = 0; i < g.getNumVertices(); ++i)
			visited.add(0);
		toExplore.addLast(v);
		Integer w; 
		while (toExplore.size() > 0)
		{
			w = toExplore.removeFirst();
			for (Integer x: g.getAdjList(w).keySet())
			{
				if (visited.get(x) == 0)
				{
					t.addEdge(w, x, g.getAdjList(w).get(x));
					toExplore.addLast(x); //breadth adds to end 
					visited.set(x, 1);
				}
			}
		}
		return t;
	}

	
	List<String> DijkstrasShortestPath(Integer t)
	{
		List<Integer> initialized = new ArrayList<Integer>();
		List<Integer> pathWeights = new ArrayList<Integer>();
		List<String> prettyWeights = new ArrayList<String>();
		
		Set<Integer> vertexSet = new HashSet<Integer>();
		
		for (int v = 0; v < g.getNumVertices(); ++v)
		{
			initialized.add(0);
			if (g.hasEdge(t, v))
			{
				initialized.set(v, 1);
				pathWeights.add(g.getEdgeWeight(t, v));
			}
			else
				pathWeights.add(0);
		}
		vertexSet.add(t);		// start at t, not 0
		initialized.set(t, 1);
		
		System.out.println("Initial weights " + pathWeights);
		
		for (int n = 0; n < g.getNumVertices(); ++n)
		{	
			Integer minimumVertex = -1;
			Integer minimumEdge = 0;
			boolean minInitialized = false;
			for (int v = 0; v < g.getNumVertices(); ++v)
			{				
				if (!vertexSet.contains(v) && initialized.get(v) == 1)
				{
					if (minInitialized == false)
					{
						minimumVertex = v;
						minimumEdge = pathWeights.get(v);
						minInitialized = true;
					}
					
					else
					{
						if (minimumEdge > pathWeights.get(v))
						{
							minimumEdge = pathWeights.get(v);
							minimumVertex = v;
						}
					}
					System.out.println(minimumVertex + " " + minimumEdge);
				}
			}
			
			if (minimumVertex > -1)
			{	
				System.out.println(minimumVertex);
				vertexSet.add(minimumVertex);
			
				for (Integer u = 0; u < g.getNumVertices(); ++u)
				{
					if (g.hasEdge(minimumVertex, u) && !vertexSet.contains(u))
					{
						if (initialized.get(u) == 0)
						{
							// mistake here
							pathWeights.set(u, pathWeights.get(minimumVertex) + g.getEdgeWeight(minimumVertex, u));
							initialized.set(u, 1);
							System.out.println(pathWeights);
						}
						else
						{
						
							if (pathWeights.get(u) > pathWeights.get(minimumVertex) + g.getEdgeWeight(minimumVertex, u))
							{
								pathWeights.set(u, pathWeights.get(minimumVertex) + g.getEdgeWeight(minimumVertex, u));
								System.out.println(pathWeights);
							}
						}
					}
				}
			}
		}
		
		for (Integer n = 0; n < g.getNumVertices(); ++n)
			if (initialized.get(n) == 1)
				prettyWeights.add(Integer.toString(pathWeights.get(n)));
			else
				prettyWeights.add("?");
		System.out.println(prettyWeights);
		return prettyWeights;
	}
}

