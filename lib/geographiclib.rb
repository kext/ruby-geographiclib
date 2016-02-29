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
      if lat1.is_a?(String) || lon1.is_a?(String)
        lat1, lon1 = GeographicLib::DMS.decode_lat_lon lat1.to_s, lon1.to_s
      end
      if azi1.is_a?(String)
        azi1 = GeographicLib::DMS.decode_azi azi1
      end
      Geodesic.direct @a, @f, lat1, lon1, azi1, !!arcmode, s12_a12
    end

    # Calculates the inverse geodesic problem given two points.
    def inverse lat1, lon1, lat2, lon2
      if lat1.is_a?(String) || lon1.is_a?(String)
        lat1, lon1 = GeographicLib::DMS.decode_lat_lon lat1.to_s, lon1.to_s
      end
      if lat2.is_a?(String) || lon2.is_a?(String)
        lat2, lon2 = GeographicLib::DMS.decode_lat_lon lat2.to_s, lon2.to_s
      end
      Geodesic.inverse @a, @f, lat1, lon1, lat2, lon2
    end

    # An instance of Geodesic initialized with the parameters for the WGS84 ellipsoid.
    WGS84 = Geodesic.new(Constants::WGS84_a, Constants::WGS84_f).freeze
  end
end
