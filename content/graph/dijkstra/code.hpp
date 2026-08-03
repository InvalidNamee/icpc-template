#pragma once

#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using i64 = long long;
using Edge = std::pair<int, i64>;  // (终点, 边权)

std::vector<i64> dijkstra(
    const std::vector<std::vector<Edge>>& graph,
    int source) {
  const i64 inf = std::numeric_limits<i64>::max() / 4;
  std::vector<i64> distance(graph.size(), inf);

  using State = std::pair<i64, int>;  // (距离, 顶点)
  std::priority_queue<
      State, std::vector<State>, std::greater<State>> queue;

  distance[source] = 0;
  queue.emplace(0, source);

  while (!queue.empty()) {
    auto [current_distance, vertex] = queue.top();
    queue.pop();
    if (current_distance != distance[vertex]) continue;

    for (auto [next, weight] : graph[vertex]) {
      i64 candidate = current_distance + weight;
      if (candidate >= distance[next]) continue;
      distance[next] = candidate;
      queue.emplace(candidate, next);
    }
  }
  return distance;
}

