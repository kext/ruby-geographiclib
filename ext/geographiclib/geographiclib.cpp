#include <ruby.h>
#include <GeographicLib/Constants.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/DMS.hpp>

static VALUE geographiclib_geodesic_direct(VALUE self, VALUE a, VALUE f, VALUE vlat1, VALUE vlon1, VALUE vazi1, VALUE arcmode, VALUE vs12_a12)
{
  GeographicLib::Geodesic g(NUM2DBL(a), NUM2DBL(f));
  GeographicLib::Math::real lat1, lon1, s12_a12, lat2, lon2, s12, azi1, azi2, m12, M12, M21, S12;
  lat1 = NUM2DBL(vlat1);
  lon1 = NUM2DBL(vlon1);
  azi1 = NUM2DBL(vazi1);
  s12_a12 = NUM2DBL(vs12_a12);
  g.GenDirect(lat1, lon1, azi1, arcmode, s12_a12, GeographicLib::Geodesic::ALL, lat2, lon2, azi2, s12, m12, M12, M21, S12);
  VALUE r = rb_hash_new();
  rb_hash_aset(r, rb_id2sym(rb_intern_const("lat1")), DBL2NUM(lat1));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("lon1")), DBL2NUM(lon1));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("lat2")), DBL2NUM(lat2));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("lon2")), DBL2NUM(lon2));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("s12")), DBL2NUM(s12));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("azi1")), DBL2NUM(azi1));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("azi2")), DBL2NUM(azi2));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("m12")), DBL2NUM(m12));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("M12")), DBL2NUM(M12));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("M21")), DBL2NUM(M21));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("S12")), DBL2NUM(S12));
  return r;
}

static VALUE geographiclib_geodesic_inverse(VALUE self, VALUE a, VALUE f, VALUE vlat1, VALUE vlon1, VALUE vlat2, VALUE vlon2)
{
  GeographicLib::Geodesic g(NUM2DBL(a), NUM2DBL(f));
  GeographicLib::Math::real lat1, lon1, lat2, lon2, s12, azi1, azi2, m12, M12, M21, S12;
  lat1 = NUM2DBL(vlat1);
  lon1 = NUM2DBL(vlon1);
  lat2 = NUM2DBL(vlat2);
  lon2 = NUM2DBL(vlon2);
  g.GenInverse(lat1, lon1, lat2, lon2, GeographicLib::Geodesic::ALL, s12, azi1, azi2, m12, M12, M21, S12);
  VALUE r = rb_hash_new();
  rb_hash_aset(r, rb_id2sym(rb_intern_const("lat1")), DBL2NUM(lat1));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("lon1")), DBL2NUM(lon1));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("lat2")), DBL2NUM(lat2));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("lon2")), DBL2NUM(lon2));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("s12")), DBL2NUM(s12));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("azi1")), DBL2NUM(azi1));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("azi2")), DBL2NUM(azi2));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("m12")), DBL2NUM(m12));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("M12")), DBL2NUM(M12));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("M21")), DBL2NUM(M21));
  rb_hash_aset(r, rb_id2sym(rb_intern_const("S12")), DBL2NUM(S12));
  return r;
}

static VALUE geographiclib_dms_decode(VALUE self, VALUE str)
{
  std::string s = rb_string_value_cstr(&str);
  try {
    GeographicLib::DMS::flag f;
    GeographicLib::Math::real angle = GeographicLib::DMS::Decode(s, f);
    VALUE r = rb_ary_new();
    rb_ary_push(r, DBL2NUM(angle));
    switch (f) {
      case GeographicLib::DMS::LATITUDE: rb_ary_push(r, rb_id2sym(rb_intern_const("lat"))); break;
      case GeographicLib::DMS::LONGITUDE: rb_ary_push(r, rb_id2sym(rb_intern_const("lon"))); break;
      case GeographicLib::DMS::AZIMUTH: rb_ary_push(r, rb_id2sym(rb_intern_const("azi"))); break;
      case GeographicLib::DMS::NUMBER: rb_ary_push(r, rb_id2sym(rb_intern_const("number"))); break;
      default: rb_ary_push(r, rb_id2sym(rb_intern_const("none"))); break;
    }
    return r;
  } catch (GeographicLib::GeographicErr) {
    rb_raise(rb_eRuntimeError, "String is malformed.");
  }
}

static VALUE geographiclib_dms_decode_lat_lon(VALUE self, VALUE vlat, VALUE vlon)
{
  std::string slat = rb_string_value_cstr(&vlat);
  std::string slon = rb_string_value_cstr(&vlon);
  try {
    GeographicLib::Math::real lat, lon;
    GeographicLib::DMS::DecodeLatLon(slat, slon, lat, lon);
    VALUE r = rb_ary_new();
    rb_ary_push(r, DBL2NUM(lat));
    rb_ary_push(r, DBL2NUM(lon));
    return r;
  } catch (GeographicLib::GeographicErr) {
    rb_raise(rb_eRuntimeError, "String is malformed.");
  }
}

static VALUE geographiclib_dms_decode_azi(VALUE self, VALUE vazi)
{
  std::string sazi = rb_string_value_cstr(&vazi);
  try {
    GeographicLib::Math::real azi;
    azi = GeographicLib::DMS::DecodeAzimuth(sazi);
    return DBL2NUM(azi);
  } catch (GeographicLib::GeographicErr) {
    rb_raise(rb_eRuntimeError, "String is malformed.");
  }
}

extern "C" void Init_geographiclib(void)
{
  VALUE geographiclib = rb_define_module("GeographicLib");
  VALUE constants = rb_define_module_under(geographiclib, "Constants");
  rb_define_const(constants, "WGS84_a", DBL2NUM(GeographicLib::Constants::WGS84_a()));
  rb_define_const(constants, "WGS84_f", DBL2NUM(GeographicLib::Constants::WGS84_f()));
  VALUE geodesic = rb_define_class_under(geographiclib, "Geodesic", rb_cObject);
  rb_define_singleton_method(geodesic, "direct", (VALUE (*)(...)) geographiclib_geodesic_direct, 7);
  rb_define_singleton_method(geodesic, "inverse", (VALUE (*)(...)) geographiclib_geodesic_inverse, 6);
  VALUE dms = rb_define_module_under(geographiclib, "DMS");
  rb_define_module_function(dms, "decode", (VALUE (*)(...)) geographiclib_dms_decode, 1);
  rb_define_module_function(dms, "decode_lat_lon", (VALUE (*)(...)) geographiclib_dms_decode_lat_lon, 2);
  rb_define_module_function(dms, "decode_azi", (VALUE (*)(...)) geographiclib_dms_decode_azi, 1);
}
