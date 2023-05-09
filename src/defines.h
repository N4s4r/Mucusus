#pragma once

// Useful for data structures that require a lot of includes
#include <bits/stdc++.h>
// BlackRed tree
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define LSOne(S) ((S) & -(S))

#define FOR(i, a, b) for (int i = (int)a; i < (int)b; ++i)
#define RFOR(i, b, a) for (int i = (int)b; i > (int)a; --i)
#define EACH(x, a) for (auto &x : a)

#define ll long long
#define ld long double
#define str string
#define vt vector
#define ii pair<int, int>
#define dd pair<double, double>
#define vi vt<int>
#define vii vt<ii>
#define vvi vt<vi>
#define pX first
#define pY second

#define MP make_pair
#define PB push_back

#define SORT(A) sort(A.begin(), A.end())
#define RSORT(A) sort(A.rbegin(), A.rend())

// BlackRed tree
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

#define PI acos(-1)
#define INF 1e9
#define EPS 1e-9
#define MOD 1e9 + 7