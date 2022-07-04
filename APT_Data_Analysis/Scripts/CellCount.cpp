/*
 *This file reads the APT_data10.txt files into a cellular array.
 counts how many atoms fall into each cell.
 presents a cel count
 *Use wisely.
 *
*/
//Input Output stream.
#include<bits/stdc++.h>

int main(){
    // Ranges of data :
    /*
    Filename : "APT_data_30mb.vtk"

    Xrange : -41.5858 to 32.8225 (delta: 74.4083)

    Yrange : -36.7009 to 36.7333 (delta: 73.4342)

    Zrange : 0.0300924 to 152.648 (delta: 152.618)
    */
    double constexpr X0 = -41.58580 ;
    double constexpr Y0 = -36.70090 ;
    double constexpr Z0 = 0.0300924 ;
    
    double Xrange = 74.4083 ;
    double Yrange = 73.4342 ;
    double Zrange = 152.618 ;
    
    // Cell size of 
    double dX = 0.1 ;
    double dY = 0.1;
    double dZ = 0.1 ;
    
    // Total cell array size 
    int Xsize = (int)std::ceil(Xrange/dX) +1 ;
    int Ysize = (int)std::ceil(Yrange/dY) +1 ;
    int Zsize = (int)std::ceil(Zrange/dZ) +1 ;
    std::cout << "No. cells: " << Xsize << " " << Ysize << " " << Zsize << std::endl ; 
    
    
    // read the APT file
    std::ifstream f("APT_data10.txt");
    if(!f){
        std::cout<<"File not found!"<<std::endl ;
        return 1;
    }
    
    //begin buffer scope
    {
        f.seekg(0,std::ios::end);
        const size_t file_size =f.tellg();
        std::string apt_data(file_size,' ');
        f.seekg(0);
        f.read(&apt_data[0],file_size);
        f.close();
        std::cout << "Fileread complete\n";
        
        // initialize a 3D vector to hold the 3D data :
        std::vector< std::vector< std::vector<int> > > CellCounts3D(Zsize, std::vector< std::vector<int> >(Ysize , std::vector<int>(Xsize)));
        std::cout << "vecinit\n";
        for(int i=0;i<Zsize;++i){
            for(int j=0;j<Ysize;++j){
                for(int k=0;k<Xsize;++k){
                    CellCounts3D[i][j][k] = 0;
                }
            }    
        }
        std::cout << "Init comlete\n";
        // Read the buffer into atomic XYZ ;
        double x, y, z, qbym ;
        int posX, posY, posZ ;
        int count ;
        //int iter = 0 ;
        std::istringstream apt_data_stream(apt_data);
        for(std::string line; std::getline(apt_data_stream, line); ){
            std::istringstream in(line);            
            in >> x >> y >> z >> qbym ;
            
            //std::cout << iter << "\n" ;
            //iter ++ ;
            
            posX = (int)std::floor((x-X0)/dX) ;
            posY = (int)std::floor((y-Y0)/dY) ;
            posZ = (int)std::floor((z-Z0)/dZ) ;
            
            //std::cout << x <<  " " << y << " " << z << std::endl ;
            //std::cout << posX <<  " " << posY << " " << posZ << std::endl ;         
            
            CellCounts3D[posZ][posY][posX] += 1 ;
        }
        
        std::cout << "Count complete\n";
        //std::cout << "No. cells: " << Xsize << " " << Ysize << " " << Zsize << std::endl ; 
        
        int totsize = Xsize*Ysize*Zsize ;
        freopen("CellularCount3D_mAPT10.vtk", "w", stdout);
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
        
    }
    
    return EXIT_SUCCESS ;
        //succesfull termination//
}
/*
 *The script ends here.
 * */
