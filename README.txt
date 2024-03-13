list team members, document who did what, discuss
anything interesting about your implementation.

Team members: Cassie Zhang xzhan304, Tianai Yue tyue4

Both Cassie and Tianai did relatively equal amounts of work and effort.

In our cache simulation, getting the cycle counts spot-on boils down to how meticulously we handle 
the intricacies, especially for cache misses where we need to factor in the extra cycles for fetching 
and potentially evicting blocks. For hits, it's crucial that we count them precisely. It's really about 
us keeping an eye on these finer details to ensure our simulator reflects real-world cache performance accurately.