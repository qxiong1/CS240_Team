//
//  main.cpp
//  cpp_self_learning
//
//  Created by michaelbern on 4/29/20.
//  Copyright © 2020 michaelbern. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

const int ECHO_SWITCH = 1;

std::string * firm_name_init(std::string * in_firms)
{
    static std::string * firms = in_firms;
    firms[0] = "Apple";
    firms[1] = "Google";
    firms[2] = "Amazon";
    firms[3] = "Facebook";
    firms[4] = "Microsoft";
    firms[5] = "Intel";
    firms[6] = "IBM";
    firms[7] = "Cisco";
    firms[8] = "Qualcomm";
    firms[9] = "Nvidia";
    
    return firms;
}
void echo_firm_name_init(std::string * in_firms)
{
    std::cout << "\n**********************************************************\nFunction Name: echo_firm_name_init\n**********************************************************" << std::endl;
    for(int i=0 ; i<10 ; i++)
    {
        std::cout << "firm[" << i << "] == " << in_firms[i] << std::endl;
    }
    std::cout << '\n' << std::endl;
}


void print_1D_Arr(double *arr)
{
    
    for(int i=0 ; i<43 ; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n' << std::endl;
}

void print_input_textfile(int arr[10][44])
{
    std::cout << "\n**********************************************************\nFunction Name: print_input_textfile \n**********************************************************" << std::endl;
    for(int i=0 ; i<10 ; i++)
       {
           for(int j=0 ; j<44 ; j++)
           {
               std::cout << arr[i][j] << ' ';
           }
           std::cout << '\n' << std::endl;
       }
}



double * changed_percentage(int arr[44])
{
    
    static double percentage_change[43];
 
    for(int i=0 ; i<43 ; i++)
    {
        percentage_change[i] = (double)(arr[i+1]-arr[i]) / arr[i];
    }
    
    return percentage_change;
}
void echo_change_percentage(double * ptr)
{
    std::cout << "\n**********************************************************\nFunction Name: echo_change_percentage\n**********************************************************" << std::endl;
    for(int i=0 ; i<43 ; i++)
    {
        std::cout << "*(ptr + " << i << ") == " << *(ptr+i) << std::endl;
    }
}


int * percentage_analysis(double * ptr)
{
    
    int grow_days = 0, down_days = 0, equal_days = 0;
    static int return_index[3];
    for(int i=0 ; i<43 ; i++)
    {
        if(*(ptr+i) < 0.0)
        {
            down_days++;
        }
        else if(*(ptr+i) > 0.0)
        {
            grow_days++;
        }
        else
        {
            equal_days++;
        }
    }
    return_index[0] = grow_days;
    return_index[1] = down_days;
    return_index[2] = equal_days;
    
    
    return return_index;
}
void echo_percentage_analysis(int * in_ptr, int firm_index)
{
    //std::cout << "\n**********************************************************\nFunction Name: echo_percentage_analysis\n**********************************************************" << std::endl;
    
    
    std::string * str = firm_name_init(str);
    
    std::cout << "Company Name: " << str[firm_index] << std::endl;
    for(int i=0 ; i<3 ; i++)
    {
        if(i==0)
        {
            std::cout << "grow days: " << in_ptr[0] << std::endl;
        }
        else if(i==1)
        {
            std::cout << "down days: " << in_ptr[1] << std::endl;
        }
        else
        {
            std::cout << "equal days: " << in_ptr[2] << std::endl;
        }
    }
    std::cout << '\n' << std::endl;
}


int main()
{
    std::string firms[10];
    firm_name_init(firms);
    std::string strArray[10][44];
    int intArray[10][44];
    int overall_up=0;
    int overall_down=0;
    double two_month_performance[10];
    double performance_average = 0.00;
    std::string suggestion = "";
    
    //read text file
    std::ifstream file("tech stock price quarterly.txt");
    if(file.is_open())
    {
        for(int i = 0; i<10; i++)
        {
            for(int j = 0; j<44; j++)
            {
                file >> strArray[i][j];
                intArray[i][j] = std::stoi(strArray[i][j]);
            }
        }
    }
  

    //call analysis functions
    for(int i=0 ; i<10 ; i++)
    {
        double * changed_percentage_ptr = changed_percentage(intArray[i]);
        int * analysis_ptr = percentage_analysis(changed_percentage_ptr);
        echo_percentage_analysis(analysis_ptr, i);
        if(analysis_ptr[0] > analysis_ptr[1])
        {
            overall_up++;
        }
        else if(analysis_ptr[0] < analysis_ptr[1])
        {
            overall_down++;
        }
        
        if(ECHO_SWITCH == 1)
        {
            echo_firm_name_init(firms);
            print_input_textfile(intArray);
            echo_change_percentage(changed_percentage_ptr);
            echo_percentage_analysis(analysis_ptr, i);
        }
        
        
        
        //performance analysis
        two_month_performance[i] = ((double)intArray[i][43] - intArray[i][0]) / intArray[i][0];
    }
    
    
    std::cout << "\n\n***Analysis***:\n\nThere are " << overall_up <<" companies have more growing dates, and " << overall_down << " companies have more down dates." << std::endl;
    for(int i=0 ; i<10 ; i++)
    {
        performance_average += two_month_performance[i];
        std::cout << firms[i] << ": " << two_month_performance[i]*100 << "%" << std::endl;
    }
    
    performance_average /= 10;
    
    std::cout << "\n\nThe average performance of tech industry in the past 2 months is: " << performance_average*100 << "%" << std::endl;
    
    
    
    if(overall_up>overall_down && performance_average>0.0)
    {
        suggestion = "Buy in for both long-term and short-term.";
    }
    else if(overall_up>overall_down && performance_average<0.0)
    {
        suggestion = "If short-term trading, buy in. If long-term holding, do Not buy.";
    }
    else if(overall_up<overall_down && performance_average>0.0)
    {
        suggestion = "If long-term holding, buy in. If short-term trading, do Not buy.";
    }
    else if(overall_up<overall_down && performance_average<0.0)
    {
        suggestion = "Do Not buy in for both short-term and long-term.";
    }
    
    
    
    std::cout << "\nThe suggestion is: " << suggestion << std::endl;
    
    
}
