public class equalfun
{
	public static void equal_fun(int a, int b, int c)
	{
		if((a == b) && ( a == c )){ System.out.println("Equal"); }
	    	else{
			System.out.println("Not equal");
	    	}
	    }
	public static void main( String[] args){
		equal_fun(1,4,5);
		equal_fun(4,4,4);
		equal_fun(6,6,6);
	}
}
