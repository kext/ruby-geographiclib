#include <ruby.h>
#include <GeographicLib/Constants.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/DMS.hpp>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#define rb_symbol(s) rb_id2sym(rb_intern_const(s))

static void decode_lat_lon(VALUE vlat, VALUE vlon, GeographicLib::Math::real &lat, GeographicLib::Math::real &lon)
{
  std::string slat, slon;
  if (rb_type(vlat) == T_STRING && rb_type(vlon) == T_STRING) {
    slat = rb_string_value_cstr(&vlat);
    slon = rb_string_value_cstr(&vlon);
    try {
      GeographicLib::DMS::DecodeLatLon(slat, slon, lat, lon);
    } catch (GeographicLib::GeographicErr e) {
      rb_raise(rb_eRuntimeError, "This is not a valid position.");
    }
  } else {
    lat = rb_num2dbl(vlat);
    lon = rb_num2dbl(vlon);
  }
}

static void decode_azi(VALUE vazi, GeographicLib::Math::real &azi)
{
  std::string sazi;
  if (rb_type(vazi) == T_STRING) {
    sazi = rb_string_value_cstr(&vazi);
    try {
      azi = GeographicLib::DMS::DecodeAzimuth(sazi);
    } catch (GeographicLib::GeographicErr e) {
      rb_raise(rb_eRuntimeError, "This is not a valid azimuth.");
    }
  } else {
    azi = rb_num2dbl(vazi);
  }
}

static VALUE geographiclib_geodesic_direct(VALUE self, VALUE a, VALUE f, VALUE vlat1, VALUE vlon1, VALUE vazi1, VALUE arcmode, VALUE vs12_a12)
{
  GeographicLib::Geodesic g(rb_num2dbl(a), rb_num2dbl(f));
  GeographicLib::Math::real lat1, lon1, s12_a12, lat2, lon2, s12, azi1, azi2, m12, M12, M21, S12;
  decode_lat_lon(vlat1, vlon1, lat1, lon1);
  decode_azi(vazi1, azi1);
  s12_a12 = rb_num2dbl(vs12_a12);
  g.GenDirect(lat1, lon1, azi1, arcmode, s12_a12, GeographicLib::Geodesic::ALL, lat2, lon2, azi2, s12, m12, M12, M21, S12);
  VALUE r = rb_hash_new();
  rb_hash_aset(r, rb_symbol("lat1"), rb_float_new(lat1));
  rb_hash_aset(r, rb_symbol("lon1"), rb_float_new(lon1));
  rb_hash_aset(r, rb_symbol("lat2"), rb_float_new(lat2));
  rb_hash_aset(r, rb_symbol("lon2"), rb_float_new(lon2));
  rb_hash_aset(r, rb_symbol("s12"), rb_float_new(s12));
  rb_hash_aset(r, rb_symbol("azi1"), rb_float_new(azi1));
  rb_hash_aset(r, rb_symbol("azi2"), rb_float_new(azi2));
  rb_hash_aset(r, rb_symbol("m12"), rb_float_new(m12));
  rb_hash_aset(r, rb_symbol("M12"), rb_float_new(M12));
  rb_hash_aset(r, rb_symbol("M21"), rb_float_new(M21));
  rb_hash_aset(r, rb_symbol("S12"), rb_float_new(S12));
  return r;
}

static VALUE geographiclib_geodesic_inverse(VALUE self, VALUE a, VALUE f, VALUE vlat1, VALUE vlon1, VALUE vlat2, VALUE vlon2)
{
  GeographicLib::Geodesic g(rb_num2dbl(a), rb_num2dbl(f));
  GeographicLib::Math::real lat1, lon1, lat2, lon2, s12, azi1, azi2, m12, M12, M21, S12;
  decode_lat_lon(vlat1, vlon1, lat1, lon1);
  decode_lat_lon(vlat2, vlon2, lat2, lon2);
  g.GenInverse(lat1, lon1, lat2, lon2, GeographicLib::Geodesic::ALL, s12, azi1, azi2, m12, M12, M21, S12);
  VALUE r = rb_hash_new();
  rb_hash_aset(r, rb_symbol("lat1"), rb_float_new(lat1));
  rb_hash_aset(r, rb_symbol("lon1"), rb_float_new(lon1));
  rb_hash_aset(r, rb_symbol("lat2"), rb_float_new(lat2));
  rb_hash_aset(r, rb_symbol("lon2"), rb_float_new(lon2));
  rb_hash_aset(r, rb_symbol("s12"), rb_float_new(s12));
  rb_hash_aset(r, rb_symbol("azi1"), rb_float_new(azi1));
  rb_hash_aset(r, rb_symbol("azi2"), rb_float_new(azi2));
  rb_hash_aset(r, rb_symbol("m12"), rb_float_new(m12));
  rb_hash_aset(r, rb_symbol("M12"), rb_float_new(M12));
  rb_hash_aset(r, rb_symbol("M21"), rb_float_new(M21));
  rb_hash_aset(r, rb_symbol("S12"), rb_float_new(S12));
  return r;
}

static VALUE geographiclib_dms_decode(VALUE self, VALUE str)
{
  std::string s = rb_string_value_cstr(&str);
  try {
    GeographicLib::DMS::flag f;
    GeographicLib::Math::real angle = GeographicLib::DMS::Decode(s, f);
    VALUE r = rb_ary_new();
    rb_ary_push(r, rb_float_new(angle));
    switch (f) {
      case GeographicLib::DMS::LATITUDE: rb_ary_push(r, rb_symbol("lat")); break;
      case GeographicLib::DMS::LONGITUDE: rb_ary_push(r, rb_symbol("lon")); break;
      case GeographicLib::DMS::AZIMUTH: rb_ary_push(r, rb_symbol("azi")); break;
      case GeographicLib::DMS::NUMBER: rb_ary_push(r, rb_symbol("number")); break;
      default: rb_ary_push(r, rb_symbol("none")); break;
    }
    return r;
  } catch (GeographicLib::GeographicErr e) {
    rb_raise(rb_eRuntimeError, "String is malformed.");
  }
}

static VALUE geographiclib_dms_decode_lat_lon(VALUE self, VALUE vlat, VALUE vlon)
{
  GeographicLib::Math::real lat, lon;
  decode_lat_lon(vlat, vlon, lat, lon);
  VALUE r = rb_ary_new();
  rb_ary_push(r, rb_float_new(lat));
  rb_ary_push(r, rb_float_new(lon));
  return r;
}

static VALUE geographiclib_dms_decode_azi(VALUE self, VALUE vazi)
{
  GeographicLib::Math::real azi;
  decode_azi(vazi, azi);
  return rb_float_new(azi);
}

static void geographiclib_local_cartesian_free(void *x)
{
  if (x) {
    delete (GeographicLib::LocalCartesian *) x;
  }
}

static size_t geographiclib_local_cartesian_size(const void *x)
{
  if (x) {
    return sizeof(GeographicLib::LocalCartesian);
  } else {
    return 0;
  }
}

static const rb_data_type_t geographiclib_local_cartesian_type = {
  "geographiclib_local_cartesian",
  {
    0,
    geographiclib_local_cartesian_free,
    geographiclib_local_cartesian_size
  },
  0,
  0,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE geographiclib_local_cartesian_alloc(VALUE klass)
{
  return TypedData_Wrap_Struct(klass, &geographiclib_local_cartesian_type, 0);
}

static GeographicLib::LocalCartesian *geographiclib_local_cartesian_get(VALUE v)
{
  GeographicLib::LocalCartesian *x;
  TypedData_Get_Struct(v, GeographicLib::LocalCartesian, &geographiclib_local_cartesian_type, x);
  if (x) {
    return x;
  } else {
    rb_raise(rb_eRuntimeError, "Object not initialized.");
  }
}

static VALUE geographiclib_local_cartesian_initialize(int argc, VALUE *argv, VALUE self)
{
  GeographicLib::Math::real lat = 0.0, lon = 0.0, h = 0.0;
  switch (argc) {
  default:
    rb_raise(rb_eArgError, "Wrong number of arguments. Expecting 0, 1, 2 or 3.");
  case 3:
    h = rb_num2dbl(argv[2]);
  case 2:
    decode_lat_lon(argv[0], argv[1], lat, lon);
  case 0:
    break;
  case 1:
    rb_check_type(argv[0], T_HASH);
    decode_lat_lon(rb_hash_lookup(argv[0], rb_symbol("lat")), rb_hash_lookup(argv[0], rb_symbol("lon")), lat, lon);
    VALUE vh = rb_hash_lookup(argv[0], rb_symbol("h"));
    if (vh != Qnil) {
      h = rb_num2dbl(vh);
    }
    break;
  }
  geographiclib_local_cartesian_free(DATA_PTR(self));
  DATA_PTR(self) = new GeographicLib::LocalCartesian(lat, lon, h);
  return self;
}

static VALUE geographiclib_local_cartesian_forward(int argc, VALUE *argv, VALUE self)
{
  GeographicLib::Math::real lat = 0.0, lon = 0.0, h = 0.0, x, y, z;
  switch (argc) {
  default:
    rb_raise(rb_eArgError, "Wrong number of arguments. Expecting 1, 2 or 3.");
  case 3:
    h = rb_num2dbl(argv[2]);
  case 2:
    decode_lat_lon(argv[0], argv[1], lat, lon);
    break;
  case 1:
    rb_check_type(argv[0], T_HASH);
    decode_lat_lon(rb_hash_lookup(argv[0], rb_symbol("lat")), rb_hash_lookup(argv[0], rb_symbol("lon")), lat, lon);
    VALUE vh = rb_hash_lookup(argv[0], rb_symbol("h"));
    if (vh != Qnil) {
      h = rb_num2dbl(vh);
    }
    break;
  }
  GeographicLib::LocalCartesian *lc = geographiclib_local_cartesian_get(self);
  lc->Forward(lat, lon, h, x, y, z);
  VALUE r = rb_hash_new();
  rb_hash_aset(r, rb_symbol("x"), rb_float_new(x));
  rb_hash_aset(r, rb_symbol("y"), rb_float_new(y));
  rb_hash_aset(r, rb_symbol("z"), rb_float_new(z));
  return r;
}

static VALUE geographiclib_local_cartesian_reverse(int argc, VALUE *argv, VALUE self)
{
  GeographicLib::Math::real lat, lon, h, x, y, z = 0.0;
  switch (argc) {
  default:
    rb_raise(rb_eArgError, "Wrong number of arguments. Expecting 1 or 3.");
  case 3:
    x = rb_num2dbl(argv[0]);
    y = rb_num2dbl(argv[1]);
    z = rb_num2dbl(argv[2]);
    break;
  case 1:
    rb_check_type(argv[0], T_HASH);
    x = rb_num2dbl(rb_hash_lookup(argv[0], rb_symbol("x")));
    y = rb_num2dbl(rb_hash_lookup(argv[0], rb_symbol("y")));
    z = rb_num2dbl(rb_hash_lookup(argv[0], rb_symbol("z")));
    break;
  }
  GeographicLib::LocalCartesian *lc = geographiclib_local_cartesian_get(self);
  lc->Reverse(x, y, z, lat, lon, h);
  VALUE r = rb_hash_new();
  rb_hash_aset(r, rb_symbol("lat"), rb_float_new(lat));
  rb_hash_aset(r, rb_symbol("lon"), rb_float_new(lon));
  rb_hash_aset(r, rb_symbol("h"), rb_float_new(h));
  return r;
}

extern "C" void Init_geographiclib(void)
{
  VALUE geographiclib = rb_define_module("GeographicLib");

  VALUE constants = rb_define_module_under(geographiclib, "Constants");
  rb_define_const(constants, "WGS84_a", rb_float_new(GeographicLib::Constants::WGS84_a()));
  rb_define_const(constants, "WGS84_f", rb_float_new(GeographicLib::Constants::WGS84_f()));

  VALUE geodesic = rb_define_class_under(geographiclib, "Geodesic", rb_cObject);
  rb_define_singleton_method(geodesic, "direct",
    (VALUE (*)(...)) geographiclib_geodesic_direct, 7);
  rb_define_singleton_method(geodesic, "inverse",
    (VALUE (*)(...)) geographiclib_geodesic_inverse, 6);

  VALUE dms = rb_define_module_under(geographiclib, "DMS");
  rb_define_module_function(dms, "decode",
    (VALUE (*)(...)) geographiclib_dms_decode, 1);
  rb_define_module_function(dms, "decode_lat_lon",
    (VALUE (*)(...)) geographiclib_dms_decode_lat_lon, 2);
  rb_define_module_function(dms, "decode_azi",
    (VALUE (*)(...)) geographiclib_dms_decode_azi, 1);

  VALUE local_cartesian = rb_define_class_under(geographiclib, "LocalCartesian", rb_cObject);
  rb_define_alloc_func(local_cartesian, geographiclib_local_cartesian_alloc);
  rb_define_method(local_cartesian, "initialize",
    (VALUE (*)(...)) geographiclib_local_cartesian_initialize, -1);
  rb_define_method(local_cartesian, "forward",
    (VALUE (*)(...)) geographiclib_local_cartesian_forward, -1);
  rb_define_method(local_cartesian, "reverse",
    (VALUE (*)(...)) geographiclib_local_cartesian_reverse, -1);
}
