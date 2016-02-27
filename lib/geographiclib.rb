require 'geographiclib/geographiclib'

module GeographicLib
  class Geodesic
    def initialize a, f
      @a = a
      @f = f
    end

    def direct lat1, lon1, azi1, arcmode, s12_a12
      Geodesic.direct @a, @f, lat1, lon1, azi1, !!arcmode, s12_a12
    end

    def inverse lat1, lon1, lat2, lon2
      Geodesic.inverse @a, @f, lat1, lon1, lat2, lon2
    end

    WGS84 = Geodesic.new Constants::WGS84_a, Constants::WGS84_f
  end
end
