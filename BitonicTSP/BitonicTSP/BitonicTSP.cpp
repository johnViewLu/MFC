// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
//int main()
//{
//    std::cout << "Hello World!\n";
//}


//// C++ program for the above approach
//#include <bits/stdc++.h>
using namespace std;

// Size of the array a[]
const int mxN = 1005;

// Structure to store the x and
// y coordinates of a point
struct Coordinates {
    double x, y;
    Coordinates(int ix = 0, int iy = 0) :x(ix), y(iy) {}
} a[mxN];

// Declare a 2-D dp array
double dp[mxN][mxN];

// Function to calculate the
// distance between two points
// in a Euclidean plane
static double distance(int i, int j)
{
    // Return the distance
    return sqrt(
        (a[i].x - a[j].x) * (a[i].x - a[j].x)
        + (a[i].y - a[j].y) * (a[i].y - a[j].y));
}

double distance_arr(int i, int j, Coordinates* a)
{
    // Return the distance
    return sqrt(
        (a[i].x - a[j].x) * (a[i].x - a[j].x)
        + (a[i].y - a[j].y) * (a[i].y - a[j].y));
}


// Utility recursive function to find
// the bitonic tour distance
static double findTourDistance(int i, int j)
{
    //std::cout << "findTourDistance:" << "i=" << i << "\t" << "j=" << j << "\n";
    // Memoization
    if (dp[i][j] == 0)
    {
        dp[i][j] = 0;
        auto a = findTourDistance(i + 1, j) + distance(i, i + 1);
        auto b = findTourDistance(i + 1, i) + distance(j, i + 1);
        dp[i][j] = std::min(a, b);
    }

    //std::cout << "findTourDistance:" << "i=" << i << "\t" << "j=" << j << "\t =" << dp[i][j] << "\n";
    if (i == j + 1)
    {
        std::cout << "Distance Traveled:" << "i=" << i << "\t" << "j=" << j << "\t =" << (25.584 - dp[i][j]) << "\n";
    }
    return dp[i][j];
}




// Function to find the
// bitonic tour distance
void bitonicTSP_recursive(int N)
{
    // Initialize the dp array
    memset(dp, 0, sizeof(dp));

    // Base Case
    for (int j = 1; j < N - 1; j++)
        dp[N - 1][j] = distance(N - 1, N)
        + distance(j, N);

    // Print the answer
    printf("%.3f\n", findTourDistance(1, 1));
}

void bitonicTSP_dynamic(int N) {
    // Initialize the dp array
    memset(dp, 0, sizeof(dp));

    // Initialize the dp array
    for (int j = 1; j < N - 1; j++)
        dp[N - 1][j] = distance(N - 1, N) + distance(j, N);

    // Calculate dp values in a bottom-up manner
    for (int i = N - 2; i >= 1; i--) {
        for (int j = i; j >= 1; j--) {
            dp[i][j] = min(dp[i + 1][j] + distance(i, i + 1), dp[i + 1][i] + distance(j, i + 1));
            std::cout << i << " " << j << "\t" << dp[i][j] << "\n";
        }
    }
    // Print the answer
    printf("%.3f\n", dp[1][1]);
}
//N = 7, arr[][] = {{0, 6}, {1 0}, {2 3}, {5 4}, {6 1}, {7 5}, {8 2}}
// Driver Code
void  bitonic_TSP_normal()
{
    const auto N = 7;
    Coordinates arr[] = { {0,0}, {0, 6}, {1, 0}, {2, 3}, {5, 4}, {6, 1}, {7, 5}, {8, 2} };
    memset(dp, 0, sizeof(dp));
    for (auto ix = 1; ix <= N; ++ix)
    {
        if (ix == 1)
            dp[1][1] = 0;
        else
            dp[1][ix] = dp[1][ix - 1] + distance_arr(ix - 1, ix, arr);
    }

    for (auto ix = 2; ix < N; ++ix)
        for (auto iy = 3; iy <= N; ++iy)
        {
            if (ix + 1 == iy)
            {
                dp[ix][iy] = dp[1][ix] + distance_arr(1, iy, arr);
                for (auto it = 2; it < ix; ++it)
                {
                    auto vTemp = dp[it][ix] + distance_arr(it, iy, arr);
                    if (vTemp < dp[ix][iy])
                        dp[ix][iy] = vTemp;
                }
            }
            else
                dp[ix][iy] = dp[ix][iy - 1] + distance_arr(iy - 1, iy, arr);

            if (ix + 1 == iy)
            {
                std::cout << ix << "," << iy << "\t" << dp[ix][iy] << "\n";
            }
        }

    std::cout << dp[N - 1][N] + distance_arr(N - 1, N, arr) << "\n";
}


void bitonicTSP_improved()
{
    const auto N = 7;
    Coordinates arr[] = { {0,0}, {0, 6}, {1, 0}, {2, 3}, {5, 4}, {6, 1}, {7, 5}, {8, 2} };
    // Initialize the dp array
    memset(dp, 0, sizeof(dp));
    dp[1][1] = 0;
    dp[2][2] = 2 * distance_arr(1, 2, arr);
    //dp[3][3] = distance_arr(1, 2,arr) + distance_arr(1, 3,arr) + distance_arr(2, 3,arr);

    for (auto i = 3; i <= N; i++)
    {
        dp[i][i] = mxN;
        double link = 0;
        for (auto j = i - 2; j >= 1; j--)
        {
            link += distance_arr(j + 1, j + 2, arr);
            double vTemp = dp[j + 1][j + 1] - distance_arr(j, j + 1, arr) + distance_arr(i, j, arr) + link;
            if (dp[i][i] > vTemp)
                dp[i][i] = vTemp;
        }
        std::cout << "i=" << i << "\t" << dp[i][i] << "\n";
    }
}

int main_bakup0()
{
    bitonicTSP_improved();
    return 0;
}

int main_bakup()
{
    // Given Input
    int N = 7;
    a[1].x = 0, a[1].y = 6;
    a[2].x = 1, a[2].y = 0;
    a[3].x = 2, a[3].y = 3;
    a[4].x = 5, a[4].y = 4;
    a[5].x = 6, a[5].y = 1;
    a[6].x = 7, a[6].y = 5;
    a[7].x = 8, a[7].y = 2;
    // Function Call

    std::cout << "dist(1,2)=" << distance(1, 2) << "\n";
    std::cout << "dist(1,3)=" << distance(1, 3) << "\n";
    std::cout << "dist(1,4)=" << distance(1, 4) << "\n";
    std::cout << "dist(2,3)=" << distance(2, 3) << "\n";
    std::cout << "dist(3,4)=" << distance(3, 4) << "\n";
    std::cout << "dist(2,4)=" << distance(2, 4) << "\n";
    std::cout << "case 2-3, 1-4 =" << distance(1, 2) + distance(2, 3) + distance(1, 4) << "\n";
    std::cout << "case 2-4, 1-3 =" << distance(1, 2) + distance(2, 4) + distance(1, 3) << "\n";
    std::cout << "case 1-2, 1-3 =" << distance(1, 2) + distance(1, 3) << "\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
