# KnapSack problem (le probleme du sac à dos)

Given weights and values of n items, put these items in a truck (it reprensents the Knaosack here) of weight capacity W anf hight capacity H to get the maximum total value in the knapsack. In other words, given two integer arrays val[0..n-1] , wt[0..n-1] and ht[0..n-1] which represent values , weights and hights associated with n items respectively. Also given two integers W which represents truck weight capacity and H which represents truck hight capacity , find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W and at the same time the sum of the hights is smaller or equal to H . You cannot break an item, either pick the complete item, or don’t pick it (0-1 property).

# Solution 

Dynamic programming is well adapted to this problem for which we can conceive an optimal solution at n variables from a subproblem at n-1 variables.We used this type of programming to implment the solution 

# How to run it 
Just donwload the .c file and run it. There is already an example hard coded.
