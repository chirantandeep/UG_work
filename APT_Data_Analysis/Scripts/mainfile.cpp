/*

 *
*/
//Input Output stream.
#include<bits/stdc++.h>

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
    double dX = 1 ;
    double dY = 1 ;
    double dZ = 1 ;
    std::cout << "Resolution(nm): "<<  dX << "," << dY << "," << dZ << std::endl ;
    
    // Total cell array size // one extra cell just in case calculations are wrong
    int Xsize = (int)std::ceil(Xrange/dX) +1 ;
    int Ysize = (int)std::ceil(Yrange/dY) +1 ;
    int Zsize = (int)std::ceil(Zrange/dZ) +1 ;
    std::cout << "No. cells: " << Xsize << " " << Ysize << " " << Zsize << std::endl ; 
    
    
    // read the APT file
    std::ifstream f("Datafiles/APT_data10.txt", std::ios::in);
    if(!f){
        std::cout<<"File not found!"<<std::endl ;
        return 1;
    }
    //std::cout << "Fileread complete\n";
    //begin buffer scope
    {
        
        // initialize a 3D vector to hold the 3D data :
        std::vector< std::vector< std::vector<int> > > CellCounts3D(Zsize, std::vector< std::vector<int> >(Ysize , std::vector<int>(Xsize)));
        //std::cout << "vecinit\n";
        for(int i=0;i<Zsize;++i){
            for(int j=0;j<Ysize;++j){
                for(int k=0;k<Xsize;++k){
                    CellCounts3D[i][j][k] = 0;
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

        // Find average :
        int tot_count = 0 ;
        int active_cells = 0 ;
        int cell_count ;
        
        for(int i=0;i<Zsize;++i){
            for(int j=0;j<Ysize;++j){
                for(int k=0;k<Xsize;++k){
                    cell_count = CellCounts3D[i][j][k] ;
                    if (cell_count>0){
                        tot_count += cell_count ;
                        active_cells += 1 ;
                    }
                }
            }    
        }
        float avg_cell_density = (float)tot_count/(float)active_cells ;
        std::cout << "Avg. active cell density: " << avg_cell_density << "\n" ;
        
        
        //std::cout << "Writing data to files\n" ;
        /*
        int totsize = Xsize*Ysize*Zsize ;
        freopen("Datafiles/trialrun.vtk", "w", stdout);
        std::cout << "# vtk DataFile Version 1.0\nDATA_FIELDS\nASCII\nDATASET STRUCTURED_POINTS\n" ;
        std::cout << "DIMENSIONS " << Xsize << " " << Ysize << " " << Zsize << "\n" ;
        std::cout << "ORIGIN 0 0 0\n" ;
        std::cout << "SPACING " << std::scientific << dX << " " << dY << " " << dZ << "\n" ;
        std::cout << "POINT_DATA " << std::defaultfloat << totsize << "\n" ;
        std::cout << "SCALARS FCC double 1\nLOOKUP_TABLE default\n" ;
    
        for(int i=0;i<Zsize;++i){
            for(int j=0;j<Ysize;++j){
                for(int k=0;k<Xsize;++k){
                    std::cout << std::scientific << CellCounts3D[i][j][k] << "\n" ;
                }
            }    
        }
        */
        
    }
    
    return EXIT_SUCCESS ;
        //succesfull termination//
}
/*
 *The script ends here.
 * */
