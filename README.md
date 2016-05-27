# GeographicLib Ruby Wrapper

Ruby wrapper for GeographicLib by Charles Karney et al.

Only the routines from Geodesic are available at the moment, sorry.
But there is more to come (eventually).

## Example

```ruby
require 'geographiclib'

# Find the distance from Wellington, NZ (41.32S, 174.81E) to
# Salamanca, Spain (40.96N, 5.50W)...
r = GeographicLib::Geodesic::WGS84.inverse(-41.32, 174.81, 40.96, -5.50)
puts "The distance is %.3f m." % r[:s12]
# This prints "The distance is 19959679.267 m."

# Find the point 20000 km SW of Perth, Australia (32.06S, 115.74E)...
r = GeographicLib::Geodesic::WGS84.direct(-32.06, 115.74, 225, false, 20000e3)
puts "The position is (%.8f, %.8f)." % [r[:lat2], r[:lon2]]
# This prints "The position is (32.11195529, -63.95925278)."
```
