public class fibonacci{
	public static int fibonacci(int N){
		if(N != 0){ int NN = fibonacci(N-1);
		return NN ;}
		else{ return 1;}
	}

	public static void main( String[] args){
		int N = Integer.parseInt(args[0]);
		int NN = fibonacci(N);
		String N_str = Integer.toString(NN);
		String NN_str = Integer.toString(N);
		System.out.println(N_str);
		System.out.println(NN_str);
		System.out.println(args[0]);
		System.out.println(args[1]);
		System.out.println(args[2]);
	}
}
