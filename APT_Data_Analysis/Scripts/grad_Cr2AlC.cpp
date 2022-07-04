/*
calculates the dragient of the apt data
 *
*/
//Input Output stream.
#include<bits/stdc++.h>
#include <omp.h>

int main(){
    // Here everything is in angstroms
    // system constants
    double ORIGIN_SHIFT = 1 ;
    double RESOLUTION = 2 ;
    
    double X0 = -192.6 - ORIGIN_SHIFT; // -192.6
    double Y0 = 0 - ORIGIN_SHIFT;
    double Z0 = 0 - ORIGIN_SHIFT;
    std::cout << "Origin(nm): "<<  X0 << "," << Y0 << "," << Z0 << std::endl ;
    
    double Xrange = 577.8;
    double Yrange = 333.593 ;
    double Zrange = 224.4 ;
    std::cout << "Ranges(nm): "<<  Xrange << "," << Yrange << "," << Zrange << std::endl ;
    
    // Cell size of in angstroms
    double dX = RESOLUTION ;
    double dY = RESOLUTION ;
    double dZ = RESOLUTION ;
    std::cout << "Resolution(nm): "<<  dX << "," << dY << "," << dZ << std::endl ;
    
    // Total cell array size // one extra cell just in case calculations are wrong
    int Xsize = (int)std::ceil(Xrange/dX) +1 ;
    int Ysize = (int)std::ceil(Yrange/dY) +1 ;
    int Zsize = (int)std::ceil(Zrange/dZ) +1 ;
    std::cout << "No. cells: " << Xsize << " " << Ysize << " " << Zsize << std::endl ; 
    
    
    // read the APT file
    std::ifstream f("Datafiles/Cr2AlC_v3.xyz", std::ios::in);
    if(!f){
        std::cout<<"File not found!"<<std::endl ;
        return 1;
    }
    //std::cout << "Fileread complete\n";
    //begin buffer scope
    {
        
        // initialize a 3D vector to hold the 3D data :
        std::vector< std::vector< std::vector<int> > > CellCounts3D(Zsize, std::vector< std::vector<int> >(Ysize , std::vector<int>(Xsize)));
        std::vector< std::vector< std::vector<int> > > CellGrad3D(Zsize, std::vector< std::vector<int> >(Ysize , std::vector<int>(Xsize)));
        //std::cout << "vecinit\n";
        for(int i=0;i<Zsize;++i){
            for(int j=0;j<Ysize;++j){
                for(int k=0;k<Xsize;++k){
                    CellCounts3D[i][j][k] = 0;
                    CellGrad3D[i][j][k] = 0;
                }
            }    
        }
        //std::cout << "Init comlete\n";
        // Read the buffer into atomic XYZ ;
        double x, y, z, qbym ;
        int posX, posY, posZ ;
        int count ;
        std::string AtID ;
        //int iter = 0 ;
        ///std::istringstream apt_data_stream(apt_data);
        // to get only 60% random atoms
        float randnum ;
        float threshold  = 0.4f ;
        for(std::string line; std::getline(f, line); ){
            std::istringstream in(line);                       
            in >> AtID >> x >> y >> z ;
            posX = (int)std::floor((x-X0)/dX) ;
            posY = (int)std::floor((y-Y0)/dY) ;
            posZ = (int)std::floor((z-Z0)/dZ) ;
            randnum = ((float)rand()/(float)RAND_MAX) ;
            if(randnum >= threshold ){
                CellCounts3D[posZ][posY][posX] += 1 ;
            }
        }

        // Find average :
        int tot_count = 0 ;
        int active_cells = 0 ;
        int C, L, R, U, D, F, B ;
        
        int grad ;
        for(int i=1;i<Zsize-1;++i){
            for(int j=1;j<Ysize-1;++j){
                for(int k=1;k<Xsize-1;++k){
                    C = CellCounts3D[i][j][k] ;
                    L = CellCounts3D[i][j][k+1] ;
                    R = CellCounts3D[i][j][k-1] ;
                    U = CellCounts3D[i+1][j][k] ;
                    D = CellCounts3D[i-1][j][k] ;
                    F = CellCounts3D[i][j+1][k] ;
                    B = CellCounts3D[i][j-1][k] ;
                    grad = L+R+U+D+F+B - 6*C ;
                    CellGrad3D[i][j][k] = grad ;
                }
            }    
        }

        int totsize = Xsize*Ysize*Zsize ;        
        std::ofstream outfilestream("./Datafiles/GradCr2AlC_res2_0p6part1.vtk");
        outfilestream << "# vtk DataFile Version 1.0\nDATA_FIELDS\nASCII\nDATASET STRUCTURED_POINTS\n" ;
        outfilestream << "DIMENSIONS " << Xsize << " " << Ysize << " " << Zsize << "\n" ;
        outfilestream << "ORIGIN 0 0 0\n" ;
        outfilestream << "SPACING " << std::scientific << dX << " " << dY << " " << dZ << "\n" ;
        outfilestream << "POINT_DATA " << std::defaultfloat << totsize << "\n" ;
        outfilestream << "SCALARS FCC double 1\nLOOKUP_TABLE default\n" ;
    
        for(int i=0;i<Zsize;++i){
            for(int j=0;j<Ysize;++j){
                for(int k=0;k<Xsize;++k){
                    outfilestream << std::scientific << CellGrad3D[i][j][k] << "\n" ;
                }
            }    
        }
        outfilestream.close();
        
    }
    
    return EXIT_SUCCESS ;
        //succesfull termination//
}
/*
 *The script ends here.
 * */
