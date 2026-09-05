std::vector<int> divisors(int n) {
  std::vector<int> result;
  for (int i = 1; 1LL * i * i <= n; ++i) {
    if (n % i == 0) {
      result.push_back(i);
      if (i != n / i) result.push_back(n / i);
    }
  }
  std::sort(result.begin(), result.end());
  return result;
}
