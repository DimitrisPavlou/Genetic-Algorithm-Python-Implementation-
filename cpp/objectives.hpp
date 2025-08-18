#pragma once 
#include <bits/stdc++.h>


using ObjectiveFunction = std::function<float(const std::vector<double>&)>;

float sphere(const std::vector<double>& x);
float banana(const std::vector<double>& x);
float powel(const std::vector<double>& x);