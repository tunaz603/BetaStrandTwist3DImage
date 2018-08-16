#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

#define DEBUG false

std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        if (token.length())
        {
            result.push_back(std::move(token));
        }
    }

    return result;
}

int main(int argc, char* argv[])
{
    double desired_dist_limit = 1.5;
    int starting_index = 0;
    
    if (argc == 2)
    {
        std::vector<std::string> args = explode(argv[1], ' ');
        
        if (args.size() > 0)
        {
            desired_dist_limit = atof(args[0].c_str());
        }
        
        if (args.size() > 1)
        {
            starting_index = atoi(args[1].c_str());
        }
    }
    else if (argc == 3)
    {
        desired_dist_limit = atof(argv[1]);
        starting_index = atoi(argv[2]);
    }
    
    // Bring in entire standard input to sstream, so we can seek through it multiple times.
    std::string current_line;
    std::stringstream input(std::ios::in|std::ios::out);
    
    // Take in and ignore "starting_index" amount of lines.
    
    for (int i = 0; i < starting_index; i++)
    {
        std::getline(std::cin, current_line);
    }
    
    for (; std::getline(std::cin, current_line);)
    {
        if (current_line.find("ATOM") == 0)
        {
            input << current_line << std::endl;
        }
        else
        {
            if (DEBUG)
            {
                std::cout << "Invalid line found and skipped" << std::endl;
            }
        }
    }
    
    input.seekg(std::ios_base::beg);
    
    std::stringstream input2(input.str());
    

    // Calculate total length of entire strand.
    
    double x_prev;
    double y_prev;
    double z_prev;
    
    double x;
    double y;
    double z;
    
    int x_pos = 6;
    
    double total_length = 0;
    
    int i = 0;
    
    for (; std::getline(input2, current_line);)
    {
        if (i == 0)
        {
            std::vector<std::string> elements = explode(current_line, ' ');
            x_prev = atof(elements[x_pos].c_str());
            y_prev = atof(elements[x_pos + 1].c_str());
            z_prev = atof(elements[x_pos + 2].c_str());
        }
        else
        {
            std::vector<std::string> elements = explode(current_line, ' ');
            x = atof(elements[x_pos].c_str());
            y = atof(elements[x_pos + 1].c_str());
            z = atof(elements[x_pos + 2].c_str());
            
            double dist = sqrt(pow(x - x_prev, 2) + pow(y - y_prev, 2) + pow(z - z_prev, 2));
            
            x_prev = x;
            y_prev = y;
            z_prev = z;
            
            total_length += dist;
        }
        
        i++;
    }
    
    if (DEBUG)
    {
        std::cout << "Total length: " << total_length << std::endl;
    }
    
    int N = 10000;
    double lower_range = 0.5;
    double upper_range = 5.0;
    
    double min_score = 9999999;
    double best_limit = 0;
    
    for (int i = 0; i < N; i++)
    {
        double t = ((float)i) / (((float)N) - 1);
        
        double val = lower_range + t * (upper_range - lower_range);
        
        double remainder = fmod(total_length, val);
        
        if (remainder >= lower_range && remainder <= upper_range)
        {
            double score = sqrt( pow(desired_dist_limit - val, 2) + pow(desired_dist_limit - remainder, 2) );
            
            if (score < min_score)
            {
                min_score = score;
                best_limit = val;
            }
        }
    }
    
    if (DEBUG)
    {
        std::cout << "Best limit: " << best_limit << std::endl;
    }
    
    double dist_limit = best_limit;
   
    
    double sum_dist = 0;
    
    int j = 1;
    
    double prev_sum_dist = 0;
    
    bool last_included = false;
    
    i = 0;
    
    std::string last_line;
    
    for (; std::getline(input, current_line);)
    {
        last_included = false;
        
        if (i == 0)
        {
            std::cout << current_line << std::endl;

            std::vector<std::string> elements = explode(current_line, ' ');
            x_prev = atof(elements[x_pos].c_str());
            y_prev = atof(elements[x_pos + 1].c_str());
            z_prev = atof(elements[x_pos + 2].c_str());
        }
        else
        {
            std::vector<std::string> elements = explode(current_line, ' ');
            x = atof(elements[x_pos].c_str());
            y = atof(elements[x_pos + 1].c_str());
            z = atof(elements[x_pos + 2].c_str());
            
            double dist = sqrt(pow(x - x_prev, 2) + pow(y - y_prev, 2) + pow(z - z_prev, 2));
            
            // std::cout << dist << std::endl;
            
            sum_dist += dist;
            
            if (sum_dist > dist_limit*j)
            {
                j++;
                std::cout << current_line << std::endl;
                double delta_sum_dist = sum_dist - prev_sum_dist;
                prev_sum_dist = sum_dist;
                
                if (DEBUG)
                {
                    std::cout << delta_sum_dist << std::endl;
                }
                
                last_included = true;
            }
            
            x_prev = x;
            y_prev = y;
            z_prev = z;
        }
        
        last_line = current_line;
        
        i++;
    }
    
    if (!last_included)
    {
        std::cout << last_line << std::endl;
        
        double delta_sum_dist = sum_dist - prev_sum_dist;
        
        if (DEBUG)
        {
            std::cout << "Last: " << delta_sum_dist << std::endl;
        }
    }
}