public class game{

/**
 * BASIC STRUCTURE
 * The first function generates a zeros quare matrix of a given
 * size .  
 * */
	public static int[][] genZeroMat(int s){
	int[][] M ;
	M = new int[s][s];
	for(int i=0; i<s;i++){
		for(int j = 0; j<s;j++){
		M[i][j]=0;
		}
	}
	return M; }

/**And a method to print such matrices.
 * */
	public static void matPrint(int[][] M){
		int s = M.length;
		String line = "-";
		while(line.length()< s*6){ line+="-----"; }
	StdOut.println(line);
		for(int i = 0 ; i<s ; i++){
			System.out.print("|");
			for(int j=0 ; j<s; j++){
				String num = Integer.toString(M[i][j]);
				for (int k = num.length() ; k<5; k++ ){
				num = " "+ num ;
				}

			System.out.print( num ) ;
			System.out.print(" ");
			}
			System.out.print("| \n");
		} 

	StdOut.println(line);
	}

/**Next we should fill this matrix witha few 2s in 
 * random positions. 
 * */
	public static int[][] genFewTwos(int[][] M){
		int n = M.length ;
		int count = StdRandom.uniform(2,3);
		while(count != 0){
			int x = StdRandom.uniform(n-1);
			int y = StdRandom.uniform(n-1);
			if(M[x][y] == 0){
				M[x][y] = 2;
				count -= 1;
			}
		}
		return M;
	}
/**
 * MATRIX MANUPULATION
 * */
	public static int[][] mat_transpose(int[][] M){
		int s = M.length ;
		int[][] M_ = genZeroMat(s) ;
		for(int i=0; i<s ; i++){
		for(int j=0; j<s; j++){
		M_[i][j] = M[j][i];
		}}
		return M_;
	}
	public static int[][] flip_ver(int[][] M){
	int s = M.length;
	int[][] M_ = new int[s][s];
	for(int i=0; i<s; i++){
	for(int j=0; j<s; j++){
		M_[i][j] = M[i][s-1-j];
	}}
	return M_ ; }

/**
 * FALL FUNCTIONS
 * */

	public static int[][] LeftFall(int[][] R){
		int s = R.length ;
		for(int j=0; j<s; j++){
		int pos = 0;
		for(int i=0; i<s; i++){
			if(R[j][i]!=0) {
			R[j][pos] = R[j][i];
			if(pos!=i){R[j][i]=0;}
			pos +=1; 
			}
		}
		/*The if condition rendered this useless
		for(int i=pos+1; i<s; i++){
		R[j][i] = 0;
		}*/
		}
		return R ;
	}

	public static int[][] add_LF(int[][] R){
		int s = R.length ;
		for(int i=0; i<s;i++){
			for(int j = 0 ; j<s-1 ; j++){
				if(R[i][j] == R[i][j+1]){
					R[i][j] += R[i][j+1];
					R[i][j+1] = 0;
				}
			}
		}
		R = LeftFall(R);
		return R ;
	}

/**
 * MAIN CONTROL FUNCTIONS
 * */
	public static int[][] LEFT(int[][] M){
	M = LeftFall(M);
	M = add_LF(M);
	return M ;
	}

	public static int[][] RIGHT(int[][] M){
		M = flip_ver(M);
		M = LEFT(M);
		M = flip_ver(M);
		return M ;
	}
	public static int[][] FALL(int[][] M){
	M = mat_transpose(M);
	M = RIGHT(M);
	M = mat_transpose(M);
	return M;
	}
	public static int[][] RAISE(int[][] M){
	M = mat_transpose(M);
	M = LEFT(M);
	M = mat_transpose(M);
	return M;
	}

/**
 * THE MAIN FUNCTION STARTS HERE
 * */
public static void main(String[] args){
	System.out.println("!!!!!!!!!!  LETS PLAY 2048 !!!!!!!!!!!!!!!!");
	System.out.println("\t q = Quit \t r = Restart");
	System.out.println(" u = RAISE  n = FALL  j = RIGHT  h = LEFT");
	int s =8;
	int[][] M;
	M = genZeroMat(s);
	M = genFewTwos(M);
	matPrint(M);
	boolean quit = false;
	while(!quit){
		String x = StdIn.readString();
		switch(x){
			case "u":
				M = RAISE(M);
				break;
			case "j":
				M = RIGHT(M);
				break;
			case "h":
				M = LEFT(M);
				break;
			case "n":
				M = FALL(M);
				break;
			case "r":
				M = genZeroMat(s);
				M = genFewTwos(M);
				System.out.println("Restarting game.");
				break;
			case "q":
				quit = true;
				break;
			default:
				;
				//System.out.println("INVALID KEY");
				//invalid = true ;
		}
		M = genFewTwos(M);
		matPrint(M);
	}

}
}
