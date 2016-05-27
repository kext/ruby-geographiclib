require 'geographiclib/geographiclib'

module GeographicLib
  class Geodesic
    attr_accessor :a, :f

    # Creates an ellipsoid with semi-major-axis a and flattening f.
    def initialize a, f
      @a = a
      @f = f
    end

    # Calculates the direct geodesic problem given a point, an azimuth and a distance.
    # If arcmode is false, the distance is in meters, otherwise it is an angle.
    def direct lat1, lon1, azi1, arcmode, s12_a12
      Geodesic.direct @a, @f, lat1, lon1, azi1, !!arcmode, s12_a12
    end

    # Calculates the inverse geodesic problem given two points.
    def inverse lat1, lon1, lat2, lon2
      Geodesic.inverse @a, @f, lat1, lon1, lat2, lon2
    end

    # An instance of Geodesic initialized with the parameters for the WGS84 ellipsoid.
    WGS84 = Geodesic.new(Constants::WGS84_a, Constants::WGS84_f).freeze
  end
end
