// bitonic_tsp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include <bits/stdc++.h>
using namespace std;
#include <vector>
namespace test {
    // Size of the array a[]
    const int mxN = 1005;
    // Structure to store the x and
    // y coordinates of a point
    struct Coordinates {
        double x, y;
        Coordinates(double ix = 0, double iy = 0) :x(ix), y(iy) {}
    } a[mxN];
    // Declare a 2-D dp array
    double dp[mxN][mxN];
    int option[mxN][mxN];
    // Function to calculate the
    // distance between two points
    // in a Euclidian plane
    double distance(int i, int j);
    // Utility recursive function to find
    // the bitonic tour distance
    double findTourDistance(int i, int j)
    {
        std::cout << "i=" << i << "\t" << "j=" << j << "\n";
        // Memoization
        if (dp[i][j] == 0)
        {
            // Update dp[i][j]
            //dp[i][j] = std::min(
            //  findTourDistance(i + 1, j) + distance(i, i + 1),
            //  findTourDistance(i + 1, i) + distance(j, i + 1));

            auto vA = findTourDistance(i + 1, j) + distance(i, i + 1);
            auto vB = findTourDistance(i + 1, i) + distance(j, i + 1);
            dp[i][j] = std::min(vA, vB);
            vA < vB ? std::cout << i : std::cout << j;
            std::cout << "\n";
        }

        std::cout << "i=" << i << "\t" << "j=" << j << " dp=" << dp[i][j] << "\n";
        return dp[i][j];
    }
    // Function to find the
    // bitonic tour distance

    Coordinates arr[] = { {0,0}, { 0, 6 }, {1, 0}, {2, 3}, {5, 4}, {6, 1}, {7, 5}, {8, 2} };
    //Coordinates arr[] = { {0,0}, {1, 0}, {2, 3},{5, 4}, {6, 1}, {7, 5}, {8, 2} };

    auto N = sizeof(arr) / sizeof(Coordinates) - 1;

    static double distance(int i, int j)
    {
        // Return the distance
        return sqrt(
            (arr[i].x - arr[j].x) * (arr[i].x - arr[j].x)
            + (arr[i].y - arr[j].y) * (arr[i].y - arr[j].y));
    }


    static void bitonicTSP(int N)
    {
        // Initialize the dp array
        memset(dp, 0, sizeof(dp));
        // Base Case
        for (int j = 1; j < N - 1; j++)
            dp[N - 1][j] = distance(N - 1, N) + distance(j, N);
        // Print the answer
        printf("%.2f\n", findTourDistance(1, 1));
    }

    static void bitonicTSP2(int N)
    {
        // Initialize the dp array
        memset(dp, 0, sizeof(dp));
        // Base Case
        for (int j = 1; j < N - 1; j++)
            dp[N - 1][j] = distance(N - 1, N) + distance(j, N);

        for (auto i = N - 2; i > 0; i--)
            for (auto j = i - 1; j > 0; j--)
            {
                auto vA = dp[i + 1][j] + distance(i, i + 1);
                auto vB = dp[i + 1][i] + distance(i + 1, j);
                dp[i][j] = std::min(vA, vB);
                if (vA < vB)
                    option[i][j] = i;
                else
                    option[i][j] = j;
               // if (i - 1 == j)
                {
                    std::cout << "(" << i << "," << j << ")\t" << dp[i][j] << "\n";
                }
            }

        // Print the answer
        printf("%.2f\n", dp[2][1] + distance(1, 2));
        std::cout << dp[1][1] << "\n";

        vector<int> traceA, traceB;
        traceA.push_back(2);
        traceB.push_back(1);
        for (auto ix = 2; ix <= N - 2; ++ix)
            for (auto iy = ix - 1; iy > 0; --iy)
            {
                std::cout << "(ix=" << ix << ",iy=" << iy << ")=" << option[ix][iy] << "\n";
                if (option[ix][iy] == traceA.back())
                {
                    traceA.push_back(ix + 1);
                    std::cout << "trace A:" << (ix + 1) << "\n";
                }
                else if (option[ix][iy] == traceB.back())
                {
                    traceB.push_back(ix + 1);
                    std::cout << "trace B:" << (ix + 1) << "\n";
                }
                else
                    std::cout << "no trace option\n";
            }
        for (auto x : traceA)
            std::cout << x << "\t";
        std::cout << "\n";
        for (auto x : traceB)
            std::cout << x << "\t";

    }


    static void bitonicTSP3(int N)
    {
        // Initialize the dp array
        memset(dp, 0, sizeof(dp));
        dp[1][1] = 0;
        dp[2][2] = 2 * distance(1, 2);
        dp[3][3] = distance(1, 2) + distance(1, 3) + distance(2, 3);

        for (auto i = 4; i <= N; i++)
        {
            dp[i][i] = mxN;
            for (auto j = 1; j < i - 1; j++)
            {
                double vTemp = 0;
                if (j == 1)
                {
                    for (auto x = 1; x <= i - 1; ++x)
                        vTemp += distance(x, x + 1);
                    vTemp += distance(1, i);
                }
                else
                {
                    vTemp = dp[j][j] - distance(j - 1, j);
                    vTemp += distance(i, j);
                    vTemp += distance(j - 1, j + 1);
                    for (auto z = j + 1; z < i; ++z)
                        vTemp += distance(z, z + 1);
                }
                if (dp[i][i] > vTemp)
                    dp[i][i] = vTemp;
            }
            std::cout << "i=" << i << "\t" << dp[i][i] << "\n";
        }
    }

    static void bitonicTSP4(int N)
    {
        for (auto i = 2; i <= N; i++)
            dp[1][i] = dp[1][i - 1] + distance(i - 1, i);

        dp[2][1] = distance(2, 1);
        dp[2][3] = dp[2][1] + distance(1, 3);
        for (auto i = 4; i <= N; ++i)
            dp[2][i] = dp[2][i - 1] + distance(i - 1, i);

        int option[] = { 0,0,1,1, 0,0,0,0 };

        for (auto i = 3; i <= N - 1; ++i)
        {
            for (auto j = i + 1; j <= N; ++j)
            {
                if (j == i + 1)
                {
                    dp[i][j] = dp[1][i] + distance(1, j);
                    option[j] = 1;
                    for (auto k = 2; k <= i - 1; ++k)
                    {
                        auto vTemp2 = dp[k][i] + distance(k, i + 1);
                        if (vTemp2 < dp[i][j])
                        {
                            dp[i][j] = vTemp2;
                            option[j] = k;
                        }
                    }
                }
                else
                    dp[i][j] = dp[i][j - 1] + distance(j - 1, j);
                std::cout << "(" << i << "," << j << ")=" << dp[i][j] << "\n";
            }
        }

        std::cout << dp[N - 1][N] + distance(N - 1, N) << "\n";
        for (auto ix = 7; ix > 1; --ix)
            std::cout << "ix=" << ix << "\t" << option[ix] << "\n";

        auto temp = N;
        while (temp > 1)
        {
            std::cout << "point " << temp << " connected " << option[temp] << "\n";
            temp = option[temp];
        }


        std::cout << "\n";
    }

}

// Driver Code
int main()
{
  memset(test::dp, 0, sizeof(test::dp));
  memset(test::option, 0, sizeof(test::option));
  //// Given Input
  //int N = 3;
  //a[1].x = 1, a[1].y = 1;
  //a[2].x = 2, a[2].y = 3;
  //a[3].x = 3, a[3].y = 1;
  // Function Call
  //bitonicTSP2(N);
  test::bitonicTSP2(test::N);
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
