#encoding: utf-8
Gem::Specification.new do |s|
  s.name        = 'geographiclib'
  s.version     = '0.0.2'
  s.date        = Time.now.strftime('%Y-%m-%d')
  s.summary     = 'GeograpicLib'
  s.description = 'A wrapper for GeograpicLib.'
  s.authors     = File.read('AUTHORS').each_line.map(&:chomp)
  s.license     = 'MIT'
  s.homepage    = 'https://github.com/kext/ruby-geographiclib'
  s.email       = '—'
  s.extensions  = ['ext/geographiclib/extconf.rb']
  s.files       = [
    'AUTHORS',
    'LICENSE',
    'lib/geographiclib.rb',
    'ext/geographiclib/Accumulator.cpp',
    'ext/geographiclib/AlbersEqualArea.cpp',
    'ext/geographiclib/AzimuthalEquidistant.cpp',
    'ext/geographiclib/CassiniSoldner.cpp',
    'ext/geographiclib/CircularEngine.cpp',
    'ext/geographiclib/DMS.cpp',
    'ext/geographiclib/Ellipsoid.cpp',
    'ext/geographiclib/EllipticFunction.cpp',
    'ext/geographiclib/extconf.rb',
    'ext/geographiclib/GARS.cpp',
    'ext/geographiclib/Geocentric.cpp',
    'ext/geographiclib/GeoCoords.cpp',
    'ext/geographiclib/Geodesic.cpp',
    'ext/geographiclib/GeodesicExact.cpp',
    'ext/geographiclib/GeodesicExactC4.cpp',
    'ext/geographiclib/GeodesicLine.cpp',
    'ext/geographiclib/GeodesicLineExact.cpp',
    'ext/geographiclib/GeographicLib/Accumulator.hpp',
    'ext/geographiclib/GeographicLib/AlbersEqualArea.hpp',
    'ext/geographiclib/GeographicLib/AzimuthalEquidistant.hpp',
    'ext/geographiclib/GeographicLib/CassiniSoldner.hpp',
    'ext/geographiclib/GeographicLib/CircularEngine.hpp',
    'ext/geographiclib/GeographicLib/Config.h',
    'ext/geographiclib/GeographicLib/Constants.hpp',
    'ext/geographiclib/GeographicLib/DMS.hpp',
    'ext/geographiclib/GeographicLib/Ellipsoid.hpp',
    'ext/geographiclib/GeographicLib/EllipticFunction.hpp',
    'ext/geographiclib/GeographicLib/GARS.hpp',
    'ext/geographiclib/GeographicLib/Geocentric.hpp',
    'ext/geographiclib/GeographicLib/GeoCoords.hpp',
    'ext/geographiclib/GeographicLib/Geodesic.hpp',
    'ext/geographiclib/GeographicLib/GeodesicExact.hpp',
    'ext/geographiclib/GeographicLib/GeodesicLine.hpp',
    'ext/geographiclib/GeographicLib/GeodesicLineExact.hpp',
    'ext/geographiclib/GeographicLib/Geohash.hpp',
    'ext/geographiclib/GeographicLib/Geoid.hpp',
    'ext/geographiclib/GeographicLib/Georef.hpp',
    'ext/geographiclib/GeographicLib/Gnomonic.hpp',
    'ext/geographiclib/GeographicLib/GravityCircle.hpp',
    'ext/geographiclib/GeographicLib/GravityModel.hpp',
    'ext/geographiclib/GeographicLib/LambertConformalConic.hpp',
    'ext/geographiclib/GeographicLib/LocalCartesian.hpp',
    'ext/geographiclib/GeographicLib/MagneticCircle.hpp',
    'ext/geographiclib/GeographicLib/MagneticModel.hpp',
    'ext/geographiclib/GeographicLib/Math.hpp',
    'ext/geographiclib/GeographicLib/MGRS.hpp',
    'ext/geographiclib/GeographicLib/NormalGravity.hpp',
    'ext/geographiclib/GeographicLib/OSGB.hpp',
    'ext/geographiclib/GeographicLib/PolarStereographic.hpp',
    'ext/geographiclib/GeographicLib/PolygonArea.hpp',
    'ext/geographiclib/GeographicLib/Rhumb.hpp',
    'ext/geographiclib/GeographicLib/SphericalEngine.hpp',
    'ext/geographiclib/GeographicLib/SphericalHarmonic.hpp',
    'ext/geographiclib/GeographicLib/SphericalHarmonic1.hpp',
    'ext/geographiclib/GeographicLib/SphericalHarmonic2.hpp',
    'ext/geographiclib/GeographicLib/TransverseMercator.hpp',
    'ext/geographiclib/GeographicLib/TransverseMercatorExact.hpp',
    'ext/geographiclib/GeographicLib/Utility.hpp',
    'ext/geographiclib/GeographicLib/UTMUPS.hpp',
    'ext/geographiclib/geographiclib.cpp',
    'ext/geographiclib/Geohash.cpp',
    'ext/geographiclib/Geoid.cpp',
    'ext/geographiclib/Georef.cpp',
    'ext/geographiclib/Gnomonic.cpp',
    'ext/geographiclib/GravityCircle.cpp',
    'ext/geographiclib/GravityModel.cpp',
    'ext/geographiclib/LambertConformalConic.cpp',
    'ext/geographiclib/LocalCartesian.cpp',
    'ext/geographiclib/MagneticCircle.cpp',
    'ext/geographiclib/MagneticModel.cpp',
    'ext/geographiclib/Math.cpp',
    'ext/geographiclib/MGRS.cpp',
    'ext/geographiclib/NormalGravity.cpp',
    'ext/geographiclib/OSGB.cpp',
    'ext/geographiclib/PolarStereographic.cpp',
    'ext/geographiclib/PolygonArea.cpp',
    'ext/geographiclib/Rhumb.cpp',
    'ext/geographiclib/SphericalEngine.cpp',
    'ext/geographiclib/TransverseMercator.cpp',
    'ext/geographiclib/TransverseMercatorExact.cpp',
    'ext/geographiclib/Utility.cpp',
    'ext/geographiclib/UTMUPS.cpp'
  ]
end
