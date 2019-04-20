#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std ;

struct vect
{
    int x_coordinate = 0;
    int y_coordinate = 0 ;
    int z_coordinate = 0 ;
};

struct cell

{
    bool obstacle  = false;
    int number = 0 ;
    bool S = false;
    bool T  = false;
};



bool input_validate (bool first , int grid_width , int grid_length ,vect& S , vect& E , cell *** Matrix) ;
void print_number(cell *** Matrix , const int grid_width , const int grid_length) ;
void print_obstacle(cell *** Matrix , const int grid_width , const int grid_length) ;
bool Soukup(vect & S , vect E , cell *** Matrix ,int &cell_count , int &vias_count);
void Backtrace (vect & E ,vect S , cell *** Matrix , int grid_width , int grid_length , int &cell_count , int &vias_count,float vias_cost );
bool Fill(vect S , vect E , cell *** Matrix , int grid_width , int grid_length , int vias_cost);
void reverse_soukup (cell *** & Matrix ,vect  S_reverse ,vect  S );
void cleanup (cell *** Matrix , int grid_width ,  int grid_length );

int main(int argc, const char * argv[]) {
    
    vect S;
    vect S_reverse ;
    vect S_copy;
    vect E;
    vect E_copy ;
    int grid_width = 0;
    int grid_length = 0 ;
    cell *** Matrix  ;
    bool  soukup = false ;
    bool fill = false ;
    bool exit = false ;
    int cell_count = 0 ;
    int vias_count = 0 ;
    float vias_cost ;
    
    cout <<"Enter Grid Width";
    cin >> grid_width ;
    
    while (grid_width < 1 )
        
    {
        cout <<"Width Less than 1, please Re-enter";
        cin >> grid_width ;
    }
    
    
    cout <<"Enter Grid Length";
    cin >> grid_length ;
    
    
    while (grid_length < 1 )
        
    {
        cout <<"Length Less than 1, please Re-enter";
        cin >>grid_length;
    }
    
    
    cout << "Enter Vias Cost";
    cin >> vias_cost ;
    
    while (vias_cost <0)
    {
        cout << "Re-enter Cost";
        cin >>vias_cost ;
    }
    
    exit = input_validate (1,grid_width , grid_length ,  S , E ,Matrix);
    
    Matrix = new cell **[grid_width];
    
    for (int i=0 ;i< grid_width ; i++)
        
        Matrix[i] = new cell *[grid_length];
    
    for (int j =0 ;j< grid_length ;j++)
        for (int i=0 ;i<grid_width ;i++)
            Matrix[i][j] = new cell [3];
    
    
    
    for (int z = 0 ; z< 3 ;z++)
        for (int j =0 ;j< grid_length ;j++)
            for (int i=0 ;i<grid_width ;i++)
            {
                Matrix[i][j][z].number =0;
                Matrix[i][j][z].obstacle = false;
                Matrix[i][j][z].S = false ;
                Matrix[i][j][z].T = false;
            }
    
    // Matrix[7][4][0].obstacle = true ;
    
    while (!exit)
    {
        double time_taken ;
        cell_count = 0 ;
        vias_count = 0 ;
        S_copy = S ;
        E_copy = E ;
        soukup = 0 ;
        fill = 0;
        clock_t t;
        t = clock();
        
        /////// Mark Cell with Source  ////////
        Matrix [S.x_coordinate] [S.y_coordinate] [S.z_coordinate].S = true ;
        cell_count ++ ;
        
        
        
        ////// Mark Cell With Target ////
        Matrix [E.x_coordinate] [E.y_coordinate][E.z_coordinate].T = true ;
        cell_count ++ ;
        
        
        
        if (S.x_coordinate == E.x_coordinate && S.y_coordinate == E.y_coordinate && S.z_coordinate == E.z_coordinate)
            cell_count -- ;
        
        
        
        soukup = Soukup(S_copy ,  E ,  Matrix ,cell_count ,vias_count) ; // changes source
        S_reverse = S_copy ;
        
        print_obstacle( Matrix , grid_width ,  grid_length);
        
        if (soukup == 0)
            
        {
            fill = Fill( S_copy ,  E , Matrix ,  grid_width ,  grid_length ,  vias_cost);
            print_number( Matrix , grid_width ,  grid_length);
            Backtrace (E_copy , S , Matrix ,  grid_width ,  grid_length , cell_count , vias_count,vias_cost );
        }
        
        if (fill == 0 && soukup == 0)
            
        {
            reverse_soukup (Matrix , S_reverse , S );
            print_obstacle( Matrix , grid_width ,  grid_length);
            cell_count -- ; //remove source from count
            cout << "No Possible Path \n" ;
        }
        else
            if (fill == 1 && soukup == 0)
            {
                print_obstacle( Matrix , grid_width ,  grid_length);
                cout << "Found Route Slow \n";
            }
            else
                if (soukup ==1 && fill ==0)
                {
                    cout << "Found Route Fast !! \n";
                }
        cleanup (Matrix , grid_width , grid_length );
        
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        
        cout << "Cost is: " << cell_count +vias_count*vias_cost <<endl;
        cout << "CPU Time is: " <<time_taken <<" seconds"<< endl ;
        
        exit = input_validate (0,grid_width , grid_length ,  S , E , Matrix);
        
    }
    return 0;
}

bool input_validate (bool first , int grid_width , int grid_length ,vect& S , vect& E , cell *** Matrix)

{
    
    bool exit = false ;
    
    cout <<"Enter Starting Point X_coordinate";
    
    cin >> S.x_coordinate ;
    
    
    
    while (S.x_coordinate >= grid_width)
        
    {
        
        cout << "Out Of Bounds,please Re-enter";
        
        cin >>  S.x_coordinate ;
        
    }
    
    
    
    if (S.x_coordinate < 0 )
        
        exit = true ;
    
    
    
    cout <<"Enter Starting Point Y_Coordinate";
    
    cin >> S.y_coordinate ;
    
    
    
    while ( S.y_coordinate >= grid_length )
        
    {
        
        cout << "Out Of Bounds, please Re-enter";
        
        cin >> S.y_coordinate ;
        
    }
    
    
    
    if (S.y_coordinate < 0)
        
        exit = true ;
    
    
    
    cout <<"Enter Starting Metal Layer";
    
    cin >> S.z_coordinate ;
    
    
    
    while (S.z_coordinate > 3 || S.z_coordinate < 1 )
        
    {
        
        cout << "Out Of Bounds, please Re-enter";
        
        cin >>  S.z_coordinate;
        
    }
    
    
    
    if (S.z_coordinate < 0)
        
        exit = true ;
    
    
    
    S.z_coordinate -= 1 ;
    
    
    
    if (!first && !exit)
        
    {
        
        while (Matrix[S.x_coordinate][S.y_coordinate][S.z_coordinate].obstacle == true )
            
        {
            
            cout <<"Source Occupied"<<endl;
            
            
            
            cout <<"Enter Starting Point X_coordinate";
            
            cin >> S.x_coordinate ;
            
            
            
            while (S.x_coordinate >= grid_width)
                
            {
                
                cout << "Out Of Bounds,please Re-enter";
                
                cin >>  S.x_coordinate ;
                
            }
            
            
            
            if (S.x_coordinate < 0 )
                
                exit = true ;
            
            
            
            cout <<"Enter Starting Point Y_Coordinate";
            
            cin >> S.y_coordinate ;
            
            
            
            while ( S.y_coordinate >= grid_length )
                
            {
                
                cout << "Out Of Bounds, please Re-enter";
                
                cin >> S.y_coordinate ;
                
            }
            
            
            
            if (S.y_coordinate < 0)
                
                exit = true ;
            
            
            
            cout <<"Enter Starting Metal Layer";
            
            cin >> S.z_coordinate ;
            
            
            
            while (S.z_coordinate > 3 || S.z_coordinate < 1 )
                
            {
                
                cout << "Out Of Bounds, please Re-enter";
                
                cin >>  S.z_coordinate;
                
            }
            
            
            
            if (S.z_coordinate < 0)
                
                exit = true ;
            
            
            
            S.z_coordinate -= 1 ;
        }
        
    }
    
    cout <<"Enter Ending Point X_coordinate";
    cin >> E.x_coordinate ;
    
    
    
    while ( E.x_coordinate >= grid_width)
        
    {
        
        cout << "Out Of Bounds,please Re-enter";
        
        cin >>  E.x_coordinate ;
        
    }
    
    
    
    if (E.x_coordinate < 0)
        
        exit = true ;
    
    
    
    cout <<"Enter Ending Point Y_Coordinate";
    
    cin >> E.y_coordinate ;
    
    
    
    while ( E.y_coordinate >= grid_length )
        
    {
        
        cout << "Out Of Bounds, please Re-enter";
        
        cin >> E.y_coordinate ;
        
    }
    
    if (E.y_coordinate < 0)
        
        exit = true ;
    
    
    
    cout <<"Enter Ending Metal Layer";
    
    cin >> E.z_coordinate ;
    
    
    
    while (E.z_coordinate > 3 || E.z_coordinate < 1 )
        
    {
        
        cout << "Out Of Bounds, please Re-enter";
        
        cin >>  E.z_coordinate;
        
    }
    
    
    
    if (E.z_coordinate < 0)
        
        exit = true ;
    
    
    
    E.z_coordinate -= 1 ;
    
    
    
    if (E.z_coordinate < 0)
        
        exit = true ;
    
    
    
    if (!first && !exit)
        
    {
        
        while (Matrix[E.x_coordinate][E.y_coordinate][E.z_coordinate].obstacle == true )
            
        {
            
            cout <<"target is Occupied"<<endl ;
            
            cout <<"Enter Ending Point X_coordinate";
            
            cin >> E.x_coordinate ;
            
            
            
            while ( E.x_coordinate >= grid_width)
                
            {
                
                cout << "Out Of Bounds,please Re-enter";
                
                cin >>  E.x_coordinate ;
                
            }
            
            
            
            if (E.x_coordinate < 0)
                
                exit = true ;
            
            
            
            cout <<"Enter Ending Point Y_Coordinate";
            
            cin >> E.y_coordinate ;
            
            
            
            while ( E.y_coordinate >= grid_length )
                
            {
                
                cout << "Out Of Bounds, please Re-enter";
                
                cin >> E.y_coordinate ;
                
            }
            
            if (E.y_coordinate < 0)
                
                exit = true ;
            
            
            
            cout <<"Enter Ending Metal Layer";
            
            cin >> E.z_coordinate ;
            
            
            
            while (E.z_coordinate > 3 || E.z_coordinate < 1 )
                
            {
                
                cout << "Out Of Bounds, please Re-enter";
                
                cin >>  E.z_coordinate;
                
            }
            
            
            
            if (E.z_coordinate < 0)
                
                exit = true ;
            
            
            
            E.z_coordinate -= 1 ;
            
            
            
        }
        
    }
    
    return exit ;
}



void print_number(cell *** Matrix, const int grid_width , const int grid_length)

{
    
    cout << "Matrix 1: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][0].number  ;
        
        if (Matrix[j][i][0].number > 9)
            
            cout << "  ";
        
        else
            
            cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    cout << "Matrix 2: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][1].number  ;
        
        if (Matrix[j][i][1].number > 9)
            
            cout << "  ";
        
        else
            
            cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    cout << "Matrix 3: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][2].number  ;
        
        if (Matrix[j][i][2].number > 9)
            
            cout << "  ";
        
        else
            
            cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
}



void print_obstacle(cell *** Matrix, const int grid_width , const int grid_length)

{
    
    cout << "Matrix 1: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][0].obstacle  ;
        
        cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    cout << "Matrix 2: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][1].obstacle  ;
        
        cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    cout << "Matrix 3: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][2].obstacle  ;
        
        cout << "   ";
        
    }
        
        cout << endl ;
        
    }
}



bool Soukup(vect & S , vect E , cell *** Matrix ,int & cell_count , int &vias_count)

{
    
    bool obstacle = false ;
    bool done = false ;
    
    while (!obstacle && !done)
        
    {
        
        if ( S.z_coordinate == 0 )
        {
            
            int x_counter = S.x_coordinate ;
            while ( x_counter != E.x_coordinate && Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle == false && Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == 0)
            {
                
                Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle = true ;
                
                if (E.x_coordinate> S.x_coordinate)
                    
                {
                    x_counter ++ ;
                    if ( Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == false )
                        cell_count ++ ;
                }
                else
                {
                    x_counter-- ;
                    if ( Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == false )
                        cell_count ++ ;
                }
            }
            
            
            
            if(x_counter == E.x_coordinate && Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == 0)
                
            {
                cout << "Reached x_coordinate of Target\n" ;
                Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle = true ;
                //Go to next metal layer
                S.x_coordinate = x_counter ;
                S.z_coordinate = 1 ;
                vias_count ++ ;
                if ( Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == false )
                    cell_count++ ;
                
            }
            
            else
                
                if (Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle == true )
                    
                {
                    
                    obstacle = true ;
                    cout << "Found Obstacle\n" ;
                    if (E.x_coordinate> S.x_coordinate)
                        
                    {
                        x_counter -- ;
                        cell_count -- ;
                    }
                    
                    else
                        
                    {
                        x_counter++;
                        cell_count -- ;
                    }
                    
                    ///Go to net metal layer
                    S.x_coordinate = x_counter ;
                    
                }
            
                else
                    
                {
                    
                    done = true ;
                    
                    Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle = true ;
                    
                    done = true ;
                    
                    cout << "Found Target \n";
                    
                }
            
        }
        
        else
            
            if ( S.z_coordinate == 2 )
                
            {
                
                int x_counter = S.x_coordinate ;
                
                while ( x_counter != E.x_coordinate && Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle == false && Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == 0)
                    
                {
                    
                    Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle = true ;
                    
                    if (E.x_coordinate> S.x_coordinate)
                        
                    {
                        
                        x_counter ++ ;
                        if ( Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == false )
                            cell_count ++ ;
                        
                    }
                    
                    else
                        
                    {
                        
                        x_counter-- ;
                        if ( Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == false )
                            cell_count++;
                        
                    }
                    
                }
                
                
                
                if(x_counter == E.x_coordinate && Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == 0)
                    
                {
                    
                    cout << "Reached x_coordinate of Target\n" ;
                    
                    Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle = true ;
                    
                    //Go to next metal layer
                    
                    S.x_coordinate = x_counter ;
                    
                    S.z_coordinate = 1 ;
                    
                    vias_count ++ ;
                    if ( Matrix[x_counter][S.y_coordinate][S.z_coordinate].T == false )
                        cell_count ++ ;
                    
                }
                
                else
                    
                    if (Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle == true )
                        
                    {
                        
                        obstacle = true ;
                        cout << "Found Obstacle\n" ;
                        
                        if (E.x_coordinate> S.x_coordinate)
                            
                        {
                            x_counter -- ;
                            cell_count --;
                        }
                        
                        else
                            
                        {
                            x_counter ++ ;
                            cell_count --;
                        }
                        
                        obstacle = true ;
                        ///Go to net metal layer
                        S.x_coordinate = x_counter ;
                    }
                
                    else
                        
                    {
                        done = true ;
                        Matrix[x_counter][S.y_coordinate][S.z_coordinate].obstacle = true ;
                        cout << "Found Target \n";\
                        done = true ;
                    }
                
            }
        
            else
                
                if ( S.z_coordinate == 1 )
                    
                {
                    
                    int y_counter = S.y_coordinate ;
                    
                    while ( y_counter != E.y_coordinate && Matrix[S.x_coordinate][y_counter][S.z_coordinate].obstacle == false && Matrix[S.x_coordinate][y_counter][S.z_coordinate].T == 0)
                        
                    {
                        
                        Matrix[S.x_coordinate][y_counter][S.z_coordinate].obstacle = true ;
                        
                        if (E.y_coordinate> S.y_coordinate)
                            
                        {
                            
                            y_counter ++ ;
                            if (Matrix[S.x_coordinate][y_counter][S.z_coordinate].T == false  && Matrix[S.x_coordinate][y_counter][S.z_coordinate].S == false)
                                cell_count++ ;
                            
                        }
                        
                        else
                            
                        {
                            
                            y_counter-- ;
                            if ( Matrix[S.x_coordinate][y_counter][S.z_coordinate].T == false && Matrix[S.x_coordinate][y_counter][S.z_coordinate].S == false)
                                cell_count++;
                            
                        }
                        
                    }
                    
                    
                    
                    if(y_counter == E.y_coordinate && Matrix[S.x_coordinate][y_counter][S.z_coordinate].T == 0)
                        
                    {
                        
                        cout << "Reached y_coordinate of Target\n" ;
                        
                        Matrix[S.x_coordinate][y_counter][S.z_coordinate].obstacle = true ;
                        
                        //Go to next metal layer
                        
                        S.y_coordinate = y_counter ;
                        
                        S.z_coordinate = 0 ;
                        
                        if (Matrix[S.x_coordinate] [S.y_coordinate][S.z_coordinate].obstacle == true  || E.z_coordinate == 2)
                            S.z_coordinate = 2;
                        vias_count ++ ;
                        if (Matrix[S.x_coordinate][y_counter][S.z_coordinate].T == false )
                            cell_count ++ ;
                        
                    }
                    
                    else
                        
                        if (Matrix[S.x_coordinate][y_counter][S.z_coordinate].obstacle == true )
                            
                        {
                            cout << "Found Obstacle\n" ;
                            obstacle = true ;
                            if (E.y_coordinate> S.y_coordinate)
                                
                            {
                                y_counter -- ;
                                cell_count-- ;
                            }
                            else
                                
                            {
                                y_counter ++ ;
                                cell_count--;
                            }
                            ///Go to net metal layer
                            S.y_coordinate = y_counter ;
                        }
                        else
                            
                        {
                            Matrix[S.x_coordinate][y_counter][S.z_coordinate].obstacle = true ;
                            cout << "Found Target \n";
                            done = true ;
                        }
                    
                }
        
    }
    
    return done ;
    
}



bool Fill(vect S , vect E , cell *** Matrix , int grid_width , int grid_length , int vias_cost)

{
    
    Matrix[S.x_coordinate][S.y_coordinate][S.z_coordinate].number = 1 ; //set source to 1
    
    bool done = false ;
    
    bool changed = true ;
    
    
    
    while (changed && !done)
        
    {
        
        changed = false ;
        
        for (int z =0 ;z< 3  ;z++)
            
            for (int j =0 ;j< grid_length ;j++)
                
                for (int i=0 ;i< grid_width ;i++ )
                    
                {
                    
                    
                    
                    if (Matrix[i][j][z].number !=0)
                        
                    {
                        
                        ////Where Can I go to from this Cell???
                        
                        if (z==0 || z==2) //metal layer 1 or 3
                            
                        {
                            
                            //////Can go right & left from this cell
                            
                            if (i+1 < grid_width && Matrix[i+1][j][z].obstacle == 0 && Matrix[i+1][j][z].number == 0)
                                
                            {
                                
                                Matrix[i+1][j][z].number = Matrix[i][j][z].number + 1;
                                
                                changed = true;
                                
                                if (Matrix[i+1][j][z].T == true) //if target
                                    
                                    done = true ; //mark done
                                
                            }
                            
                            
                            
                            if (i-1 >=0 && Matrix[i-1][j][z].obstacle == 0 && Matrix[i-1][j][z].number == 0)
                                
                            {
                                
                                Matrix[i-1][j][z].number = Matrix[i][j][z].number + 1;
                                
                                changed = true;
                                
                                if (Matrix[i-1][j][z].T == true) //if target
                                    
                                    done = true ; //mark done
                                
                            }
                            
                            //////Cannot Go up or down
                            
                            
                            
                        }
                        
                        else //metal layer 2
                            
                        {
                            
                            //////Can go up & down
                            
                            if (j+1 < grid_length && Matrix[i][j+1][z].obstacle == 0 && Matrix[i][j+1][z].number == 0)
                                
                            {
                                
                                Matrix[i][j+1][z].number = Matrix[i][j][z].number + 1;
                                
                                changed = true;
                                
                                if (Matrix[i][j+1][z].T == true) //if target
                                    
                                    done = true ; //mark done
                                
                            }
                            
                            
                            
                            if (j-1 >=0 && Matrix[i][j-1][z].obstacle == 0 && Matrix[i][j-1][z].number == 0)
                                
                            {
                                
                                Matrix[i][j-1][z].number = Matrix[i][j][z].number + 1;
                                
                                changed = true;
                                
                                if (Matrix[i][j-1][z].T == true) //if target
                                    
                                    done = true ; //mark done
                                
                            }
                            
                            
                            
                            //Cannot go right or left
                            
                        }
                        
                        
                        
                        /////////Can Always go above and below from cell
                        
                        if (z+1 < 3 && Matrix[i][j][z+1].obstacle == 0 && Matrix[i][j][z+1].number == 0)
                            
                        {
                            
                            Matrix[i][j][z+1].number = Matrix[i][j][z].number + vias_cost;
                            
                            changed = true;
                            
                            if (Matrix[i][j][z+1].T == true) //if target
                                
                                done = true ; //mark done
                            
                        }
                        
                        
                        
                        if (z-1 >=0 && Matrix[i][j][z-1].obstacle == 0 && Matrix[i][j][z-1].number == 0)
                            
                        {
                            
                            Matrix[i][j][z-1].number = Matrix[i][j][z].number + vias_cost;
                            
                            changed = true;
                            
                            if (Matrix[i][j][z-1].T == true) //if target
                                
                                done = true ; //mark done
                            
                        }
                        
                        
                        
                    }
                    
                }
        
    }
    
    return done ;
    
}





void Backtrace (vect & E ,vect S , cell *** Matrix , int grid_width , int grid_length , int &cell_count , int &vias_count , float vias_cost)

{
    
    int number = Matrix[E.x_coordinate][E.y_coordinate][E.z_coordinate].number - 1; //starting number
    
    
    
    while(number > 1) //reached source
        
    {
        
        Matrix[E.x_coordinate][E.y_coordinate][E.z_coordinate].obstacle = true;
        
        
        
        if (E.z_coordinate == 1) //at Metal 2
            
        {
            
            
            
            if (E.y_coordinate -1 >= 0 && Matrix[E.x_coordinate][E.y_coordinate-1][E.z_coordinate].number == number) //search up
                
            {
                
                E.y_coordinate -- ;
                
                number-- ;
                
                cell_count++ ;
                
            }
            
            else
                
                if (E.y_coordinate+1 < grid_length && Matrix[E.x_coordinate][E.y_coordinate+1][E.z_coordinate].number == number) //search down
                    
                {
                    
                    E.y_coordinate ++ ;
                    
                    number --;
                    
                    cell_count++ ;
                    
                    
                    
                }
            
                else
                    
                    if ( E.z_coordinate-1 >=0 && Matrix[E.x_coordinate][E.y_coordinate][E.z_coordinate-1].number == number+1-vias_cost) //search below
                        
                    {
                        
                        vias_count ++ ;
                        
                        E.z_coordinate -- ;
                        
                        number = number - vias_cost  ;
                        
                        cell_count++ ;
                        
                        
                        
                    }
            
                    else
                        
                        if ( E.z_coordinate+1 < 3 && Matrix[E.x_coordinate][E.y_coordinate][E.z_coordinate+1].number == number+1-vias_cost) //search above
                            
                        {
                            
                            vias_count ++ ;
                            
                            E.z_coordinate ++ ;
                            
                            number = number - vias_cost  ;
                            
                            cell_count++ ;
                            
                            
                            
                        }
            
                        else
                            
                            cout <<"Backtracing Error"; //cannot go vertical
            
            
            
        }
        
        else //at Metal 1 or 3
            
        {
            
            
            
            if (E.x_coordinate-1 >= 0 && Matrix[E.x_coordinate-1][E.y_coordinate][E.z_coordinate].number == number) //search left
                
            {
                
                E.x_coordinate -- ;
                
                number-- ;
                
                cell_count++ ;
                
                
                
            }
            
            else
                
                if (E.x_coordinate+1 < grid_width && Matrix[E.x_coordinate+1][E.y_coordinate][E.z_coordinate].number == number) //search right
                    
                {
                    
                    E.x_coordinate ++ ;
                    
                    number --;
                    
                    cell_count++ ;
                    
                    
                    
                }
            
                else
                    
                    if ( E.z_coordinate-1 >=0 && Matrix[E.x_coordinate][E.y_coordinate][E.z_coordinate-1].number == number+1-vias_cost) //search below
                        
                    {
                        
                        vias_count ++ ;
                        
                        E.z_coordinate -- ;
                        
                        number = number - vias_cost ;
                        
                        cell_count++ ;
                        
                        
                        
                    }
            
                    else
                        
                        if ( E.z_coordinate+1 < 3 && Matrix[E.x_coordinate][E.y_coordinate][E.z_coordinate+1].number == number+1-vias_cost) //search above
                            
                        {
                            
                            vias_count ++ ;
                            
                            E.z_coordinate ++ ;
                            
                            number=  number - vias_cost ;
                            
                            cell_count++ ;
                            
                            
                            
                        }
            
                        else
                            
                            cout <<"Backtracing Error"; //cannot go vertical
            
            
            
        }
        
        
        
    }
    
    
    
    cell_count -- ; //recounts source !!
    
    
    
}



void cleanup (cell *** Matrix , int grid_width, int grid_length )

{
    
    for (int z=0 ;z< 3 ;z++)
        
        for (int j=0 ;j<grid_length ; j++)
            
            for (int i =0 ;i< grid_width ;i++)
                
            {
                
                Matrix[i][j][z].number = 0 ;
                
                Matrix[i][j][z].S = 0;
                
                Matrix[i][j][z].T = 0;
                
            }
    
}



void reverse_soukup (cell *** &Matrix ,vect  S_reverse ,vect  S )

{
    
    int counter ;
    
    if (S.z_coordinate == 0 || S.z_coordinate == 2 )
        
    {
        
        Matrix[S_reverse.x_coordinate][S_reverse.y_coordinate][S_reverse.z_coordinate].obstacle = false ;
        
        if (S_reverse.x_coordinate > S.x_coordinate) //to left of source
            
        {
            
            counter = S_reverse.x_coordinate-1 ;
            
            while (counter >= S.x_coordinate)
                
            {
                
                Matrix[counter][S_reverse.y_coordinate][S_reverse.z_coordinate].obstacle = 0 ;
                
                counter -- ;
                
            }
            
        }
        
        else // to right of source
            
        {
            
            counter = S_reverse.x_coordinate + 1 ;
            
            while (counter <= S.x_coordinate)
                
            {
                
                Matrix[counter][S_reverse.y_coordinate][S_reverse.z_coordinate].obstacle = 0 ;
                
                counter ++ ;
                
            }
            
        }
        
        
        
    }
    
    else //metal 2
        
    {
        
        Matrix[S_reverse.x_coordinate][S_reverse.y_coordinate][S_reverse.z_coordinate].obstacle = false ;
        
        if (S_reverse.y_coordinate > S.y_coordinate) //to below sorce
            
        {
            
            counter = S_reverse.y_coordinate-1 ;
            
            while (counter >= S.y_coordinate)
                
            {
                
                Matrix[S_reverse.x_coordinate][counter][S_reverse.z_coordinate].obstacle = 0 ;
                
                counter -- ;
                
            }
            
        }
        
        else //above source
            
        {
            
            counter = S_reverse.y_coordinate+1 ;
            
            while (counter <= S.y_coordinate)
                
            {
                
                Matrix[S_reverse.x_coordinate][counter][S_reverse.z_coordinate].obstacle = 0 ;
                
                counter ++ ;
                
            }
            
        }
        
    }
    
}

