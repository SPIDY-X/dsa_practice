class Solution {
public:
    // Return minimum time required for every node to receive the signal.
    long long networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Use a wide sentinel outside valid accumulated times.
        const long long INF = numeric_limits<long long>::max() / 4;
 
        // Store shortest signal time using long long.
        vector<long long> dist(n + 1, INF);
 
        // Source receives the signal immediately.
        dist[k] = 0;
 
        // Propagate shortest distances through at most n - 1 edge rounds.
        for (int pass = 1; pass <= n - 1; pass++) {
            bool changed = false;
 
            // Relax every directed edge in input order.
            for (const vector<int>& edge : times) {
                int from = edge[0];
                int to = edge[1];
                long long travelTime = edge[2];
 
                // Ignore edges whose starting node remains unreachable.
                if (dist[from] == INF) {
                    continue;
                }
 
                // Record a faster signal arrival.
                if (dist[from] + travelTime < dist[to]) {
                    dist[to] = dist[from] + travelTime;
                    changed = true;
                }
            }
 
            // Stop after a round without any improvement.
            if (!changed) {
                break;
            }
        }
 
        long long answer = 0;
 
        // Find the last signal arrival among all nodes.
        for (int node = 1; node <= n; node++) {
            // If any node is unreachable, signal cannot reach all nodes.
            if (dist[node] == INF) {
                return -1;
            }
 
            // Track the maximum shortest distance.
            answer = max(answer, dist[node]);
 
            // Stop after processing the last valid node.
            if (node == n) {
                break;
            }
        }
 
        // Return the time when the last node receives the signal.
        return answer;
    }
};
 
