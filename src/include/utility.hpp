#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <time.h>
#include <sys/time.h>
#include <string>

namespace Neuro
{
    /*------------------------------------------------------------*/
    double get_wall_time()
    {
        /*! 
        measure real passed time 
        \return wall time in second
        */
        
        struct timeval time;
        if (gettimeofday(&time, NULL))
        {
            //  Handle error
            return 0;
        }
        return (double)time.tv_sec + (double)time.tv_usec * .000001;
    }
    /*------------------------------------------------------------*/
    double get_cpu_time()
    {
        /*! 
        measure cpu passed time
        \return cpu time in second
        */

        return (double)clock() / CLOCKS_PER_SEC;
    }
    /*------------------------------------------------------------*/
    void display_timing(double wtime, double cptime)
    {
        /*!
        Display wall time and cpu time on terminal
        
        */
        int wh, ch;
        int wmin, cpmin;
        double wsec, csec;
        wh = (int)wtime / 3600;
        ch = (int)cptime / 3600;
        wmin = ((int)wtime % 3600) / 60;
        cpmin = ((int)cptime % 3600) / 60;
        wsec = wtime - (3600. * wh + 60. * wmin);
        csec = cptime - (3600. * ch + 60. * cpmin);
        printf("Wall Time : %d hours and %d minutes and %.4f seconds.\n", wh, wmin, wsec);
        printf ("CPU  Time : %d hours and %d minutes and %.4f seconds.\n",ch,cpmin,csec);
    }

} // namespace Neuro

#endif // !UTILITY_HPP