/*

*/
//Input Output stream.
#include<bits/stdc++.h>

int main(int args, char* argv[]){
    
    
    // here things are in angstroms
    double constexpr X0 = -72.225; // -72.225
    double constexpr Y0 = 0 ;
    double constexpr Z0 = 0 ;
    std::cout << "Origin(nm): "<<  X0 << "," << Y0 << "," << Z0 << std::endl ;
    
    double Xrange = 216.675;
    double Yrange = 125.097 ;
    double Zrange = 100.98 ;
    std::cout << "Ranges(nm): "<<  Xrange << "," << Yrange << "," << Zrange << std::endl ;
    
    // Cell size of 
    double dX = 1.9 ;
    double dY = 1.9 ;
    double dZ = 1.9 ;
    std::cout << "Resolution(nm): "<<  dX << "," << dY << "," << dZ << std::endl ;
    
    // Total cell array size 
    int Xsize = (int)std::ceil(Xrange/dX) +1 ;
    int Ysize = (int)std::ceil(Yrange/dY) +1 ;
    int Zsize = (int)std::ceil(Zrange/dZ) +1 ;
    std::cout << "No. cells: " << Xsize << " " << Ysize << " " << Zsize << std::endl ; 
    
    
    // read the APT file
    std::ifstream f("Datafiles/Cr2AlC_v2.xyz", std::ios::in);
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
        double x, y, z;
        int posX, posY, posZ ;
        int count ;
        std::string AtID ;
        //int iter = 0 ;
        ///std::istringstream apt_data_stream(apt_data);
        for(std::string line; std::getline(f, line); ){
            //std::cout << "Init comlete\n";
            std::istringstream in(line);            
            in >> AtID >> x >> y >> z ;
            //std::cout << "Init comlete\n";
            
            //std::cout << iter << "\n" ;
            //iter ++ ;
            
            posX = (int)std::floor((x-X0)/dX) ;
            posY = (int)std::floor((y-Y0)/dY) ;
            posZ = (int)std::floor((z-Z0)/dZ) ;
            
            //std::cout << x <<  "," << y << "," << z << "\n" ;
            //std::cout << posX <<  " " << posY << " " << posZ << std::endl ;
            
            CellCounts3D[posZ][posY][posX] += 1 ;
        }
        
        //std::cout << "Count complete\n";
        
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
        
        int totsize = Xsize*Ysize*Zsize ;
        std::ofstream outfilestream("Datafiles/trialrun.vtk");
        outfilestream << "# vtk DataFile Version 1.0\nDATA_FIELDS\nASCII\nDATASET STRUCTURED_POINTS\n" ;
        outfilestream << "DIMENSIONS " << Xsize << " " << Ysize << " " << Zsize << "\n" ;
        outfilestream << "ORIGIN 0 0 0\n" ;
        outfilestream << "SPACING " << std::scientific << dX << " " << dY << " " << dZ << "\n" ;
        outfilestream << "POINT_DATA " << std::defaultfloat << totsize << "\n" ;
        outfilestream << "SCALARS FCC double 1\nLOOKUP_TABLE default\n" ;
    
        for(int i=0;i<Zsize;++i){
            for(int j=0;j<Ysize;++j){
                for(int k=0;k<Xsize;++k){
                    outfilestream << std::scientific << CellCounts3D[i][j][k] << "\n" ;
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
