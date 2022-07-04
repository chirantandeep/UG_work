/*
calculates the dragient of the apt data with a 26 point stencil. 
+ve gradient (+1) means high concentration inside cuz its (C-v/26)
-ve grad means high conc outsize. low conc inside here. 
 *
*/
//Input Output stream.
#include<bits/stdc++.h>
#include <omp.h>

int main(){
    // Here everything is in nanometers
    
    double constexpr X0 = -42 ; // -41.9109
    double constexpr Y0 = -37 ; // -36.8724
    double constexpr Z0 = 0 ; // 0.0134156
    std::cout << "Origin(nm): "<<  X0 << "," << Y0 << "," << Z0 << std::endl ;
    
    double Xrange = 75 ; // 74.8688 field 0
    double Yrange = 75 ; // 73.9253 field 1
    double Zrange = 153 ; // 152.6345844 field 2
    std::cout << "Ranges(nm): "<<  Xrange << "," << Yrange << "," << Zrange << std::endl ;
    
    // Cell size of in nanometers
    double RESOLUTION = 0.321 ;
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
    std::ifstream f("Datafiles/APT_dataALL.txt", std::ios::in);
    if(!f){
        std::cout<<"File not found!"<<std::endl ;
        return 1;
    }
    //std::cout << "Fileread complete\n";
    //begin buffer scope
    {
        
        // initialize a 3D vector to hold the 3D data :
        std::vector< std::vector< std::vector<int> > > CellCounts3D(Zsize, std::vector< std::vector<int> >(Ysize , std::vector<int>(Xsize)));
        std::vector< std::vector< std::vector<float> > > CellGrad3D(Zsize, std::vector< std::vector<float> >(Ysize , std::vector<float>(Xsize)));
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
        //int iter = 0 ;
        ///std::istringstream apt_data_stream(apt_data);
        for(std::string line; std::getline(f, line); ){
            std::istringstream in(line);            
            in >> x >> y >> z >> qbym ;
            posX = (int)std::floor((x-X0)/dX) ;
            posY = (int)std::floor((y-Y0)/dY) ;
            posZ = (int)std::floor((z-Z0)/dZ) ;
            CellCounts3D[posZ][posY][posX] += 1 ;
        }
        std::cout << "Read-done!\n" ;

        // Find average :
        int tot_count = 0 ;
        int active_cells = 0 ;
        int C;
        float grad, v;
        for(int i=1;i<Zsize-1;++i){
            for(int j=1;j<Ysize-1;++j){
                for(int k=1;k<Xsize-1;++k){
                    // Center
                    C = CellCounts3D[i][j][k] ;
                    v = 0 ;
                    // 6 point stencil - center points
                    v += CellCounts3D[i][j][k+1] ;
                    v += CellCounts3D[i][j][k-1] ;
                    v += CellCounts3D[i+1][j][k] ;
                    v += CellCounts3D[i-1][j][k] ;
                    v += CellCounts3D[i][j+1][k] ;
                    v += CellCounts3D[i][j-1][k] ;
                    // edge center points
                    v += CellCounts3D[i][j+1][k+1] ;
                    v += CellCounts3D[i][j+1][k-1] ;
                    v += CellCounts3D[i][j-1][k+1] ;
                    v += CellCounts3D[i][j-1][k-1] ;
                    
                    v += CellCounts3D[i+1][j+1][k] ;
                    v += CellCounts3D[i+1][j-1][k] ;
                    v += CellCounts3D[i-1][j+1][k] ;
                    v += CellCounts3D[i-1][j-1][k] ;
                    
                    v += CellCounts3D[i+1][j][k+1] ;
                    v += CellCounts3D[i+1][j][k-1] ;
                    v += CellCounts3D[i-1][j][k+1] ;
                    v += CellCounts3D[i-1][j][k-1] ;
                    // corner points
                    v += CellCounts3D[i+1][j+1][k+1] ;
                    v += CellCounts3D[i+1][j+1][k-1] ;
                    v += CellCounts3D[i+1][j-1][k+1] ;
                    v += CellCounts3D[i+1][j-1][k-1] ;
                    
                    v += CellCounts3D[i-1][j+1][k+1] ;
                    v += CellCounts3D[i-1][j+1][k-1] ;
                    v += CellCounts3D[i-1][j-1][k+1] ;
                    v += CellCounts3D[i-1][j-1][k-1] ;
                    
                    grad = 1.0*C - (v/26.0) ;
                    if (grad == 0){
                        CellGrad3D[i][j][k] = 0.0 ;
                    } else if (grad > 0){
                        CellGrad3D[i][j][k] += 1 ;
                    } else {
                        CellGrad3D[i][j][k] -= 1 ;
                    }
                    
                }
            }    
        }

        int totsize = Xsize*Ysize*Zsize ;        
        std::ofstream outfilestream("./Datafiles/GradAPT_res0p321_sign.vtk");
        outfilestream << "# vtk DataFile Version 1.0\nDATA_FIELDS\nASCII\nDATASET STRUCTURED_POINTS\n" ;
        outfilestream << "DIMENSIONS " << Xsize << " " << Ysize << " " << Zsize << "\n" ;
        outfilestream << "ORIGIN 0 0 0\n" ;
        outfilestream << "SPACING " << std::scientific << dX << " " << dY << " " << dZ << "\n" ;
        outfilestream << "POINT_DATA " << std::defaultfloat << totsize << "\n" ;
        outfilestream << "SCALARS FCC double 1\nLOOKUP_TABLE default\n" ;
    
        for(int i=0;i<Zsize;++i){
            for(int j=0;j<Ysize;++j){
                for(int k=0;k<Xsize;++k){
                    outfilestream << std::setprecision(2) << CellGrad3D[i][j][k] << "\n" ;
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
