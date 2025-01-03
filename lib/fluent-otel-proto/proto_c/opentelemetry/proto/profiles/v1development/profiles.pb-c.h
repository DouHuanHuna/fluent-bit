/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: opentelemetry/proto/profiles/v1development/profiles.proto */

#ifndef PROTOBUF_C_opentelemetry_2fproto_2fprofiles_2fv1development_2fprofiles_2eproto__INCLUDED
#define PROTOBUF_C_opentelemetry_2fproto_2fprofiles_2fv1development_2fprofiles_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "opentelemetry/proto/common/v1/common.pb-c.h"
#include "opentelemetry/proto/resource/v1/resource.pb-c.h"
#include "opentelemetry/proto/profiles/v1development/pprofextended.pb-c.h"

typedef struct Opentelemetry__Proto__Profiles__V1development__ProfilesData Opentelemetry__Proto__Profiles__V1development__ProfilesData;
typedef struct Opentelemetry__Proto__Profiles__V1development__ResourceProfiles Opentelemetry__Proto__Profiles__V1development__ResourceProfiles;
typedef struct Opentelemetry__Proto__Profiles__V1development__ScopeProfiles Opentelemetry__Proto__Profiles__V1development__ScopeProfiles;
typedef struct Opentelemetry__Proto__Profiles__V1development__ProfileContainer Opentelemetry__Proto__Profiles__V1development__ProfileContainer;


/* --- enums --- */


/* --- messages --- */

/*
 * ProfilesData represents the profiles data that can be stored in persistent storage,
 * OR can be embedded by other protocols that transfer OTLP profiles data but do not
 * implement the OTLP protocol.
 * The main difference between this message and collector protocol is that
 * in this message there will not be any "control" or "metadata" specific to
 * OTLP protocol.
 * When new fields are added into this message, the OTLP request MUST be updated
 * as well.
 */
struct  Opentelemetry__Proto__Profiles__V1development__ProfilesData
{
  ProtobufCMessage base;
  /*
   * An array of ResourceProfiles.
   * For data coming from a single resource this array will typically contain
   * one element. Intermediary nodes that receive data from multiple origins
   * typically batch the data before forwarding further and in that case this
   * array will contain multiple elements.
   */
  size_t n_resource_profiles;
  Opentelemetry__Proto__Profiles__V1development__ResourceProfiles **resource_profiles;
};
#define OPENTELEMETRY__PROTO__PROFILES__V1DEVELOPMENT__PROFILES_DATA__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&opentelemetry__proto__profiles__v1development__profiles_data__descriptor) \
    , 0,NULL }


/*
 * A collection of ScopeProfiles from a Resource.
 */
struct  Opentelemetry__Proto__Profiles__V1development__ResourceProfiles
{
  ProtobufCMessage base;
  /*
   * The resource for the profiles in this message.
   * If this field is not set then no resource info is known.
   */
  Opentelemetry__Proto__Resource__V1__Resource *resource;
  /*
   * A list of ScopeProfiles that originate from a resource.
   */
  size_t n_scope_profiles;
  Opentelemetry__Proto__Profiles__V1development__ScopeProfiles **scope_profiles;
  /*
   * The Schema URL, if known. This is the identifier of the Schema that the resource data
   * is recorded in. To learn more about Schema URL see
   * https://opentelemetry.io/docs/specs/otel/schemas/#schema-url
   * This schema_url applies to the data in the "resource" field. It does not apply
   * to the data in the "scope_profiles" field which have their own schema_url field.
   */
  char *schema_url;
};
#define OPENTELEMETRY__PROTO__PROFILES__V1DEVELOPMENT__RESOURCE_PROFILES__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&opentelemetry__proto__profiles__v1development__resource_profiles__descriptor) \
    , NULL, 0,NULL, (char *)protobuf_c_empty_string }


/*
 * A collection of ProfileContainers produced by an InstrumentationScope.
 */
struct  Opentelemetry__Proto__Profiles__V1development__ScopeProfiles
{
  ProtobufCMessage base;
  /*
   * The instrumentation scope information for the profiles in this message.
   * Semantically when InstrumentationScope isn't set, it is equivalent with
   * an empty instrumentation scope name (unknown).
   */
  Opentelemetry__Proto__Common__V1__InstrumentationScope *scope;
  /*
   * A list of ProfileContainers that originate from an instrumentation scope.
   */
  size_t n_profiles;
  Opentelemetry__Proto__Profiles__V1development__ProfileContainer **profiles;
  /*
   * The Schema URL, if known. This is the identifier of the Schema that the metric data
   * is recorded in. To learn more about Schema URL see
   * https://opentelemetry.io/docs/specs/otel/schemas/#schema-url
   * This schema_url applies to all profiles in the "profiles" field.
   */
  char *schema_url;
};
#define OPENTELEMETRY__PROTO__PROFILES__V1DEVELOPMENT__SCOPE_PROFILES__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&opentelemetry__proto__profiles__v1development__scope_profiles__descriptor) \
    , NULL, 0,NULL, (char *)protobuf_c_empty_string }


/*
 * A ProfileContainer represents a single profile. It wraps pprof profile with OpenTelemetry specific metadata.
 */
struct  Opentelemetry__Proto__Profiles__V1development__ProfileContainer
{
  ProtobufCMessage base;
  /*
   * A globally unique identifier for a profile. The ID is a 16-byte array. An ID with
   * all zeroes is considered invalid.
   * This field is required.
   */
  ProtobufCBinaryData profile_id;
  /*
   * start_time_unix_nano is the start time of the profile.
   * Value is UNIX Epoch time in nanoseconds since 00:00:00 UTC on 1 January 1970.
   * This field is semantically required and it is expected that end_time >= start_time.
   */
  uint64_t start_time_unix_nano;
  /*
   * end_time_unix_nano is the end time of the profile.
   * Value is UNIX Epoch time in nanoseconds since 00:00:00 UTC on 1 January 1970.
   * This field is semantically required and it is expected that end_time >= start_time.
   */
  uint64_t end_time_unix_nano;
  /*
   * attributes is a collection of key/value pairs. Note, global attributes
   * like server name can be set using the resource API. Examples of attributes:
   *     "/http/user_agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36"
   *     "/http/server_latency": 300
   *     "abc.com/myattribute": true
   *     "abc.com/score": 10.239
   * The OpenTelemetry API specification further restricts the allowed value types:
   * https://github.com/open-telemetry/opentelemetry-specification/blob/main/specification/common/README.md#attribute
   * Attribute keys MUST be unique (it is not allowed to have more than one
   * attribute with the same key).
   */
  size_t n_attributes;
  Opentelemetry__Proto__Common__V1__KeyValue **attributes;
  /*
   * dropped_attributes_count is the number of attributes that were discarded. Attributes
   * can be discarded because their keys are too long or because there are too many
   * attributes. If this value is 0, then no attributes were dropped.
   */
  uint32_t dropped_attributes_count;
  /*
   * Specifies format of the original payload. Common values are defined in semantic conventions. [required if original_payload is present]
   */
  char *original_payload_format;
  /*
   * Original payload can be stored in this field. This can be useful for users who want to get the original payload.
   * Formats such as JFR are highly extensible and can contain more information than what is defined in this spec.
   * Inclusion of original payload should be configurable by the user. Default behavior should be to not include the original payload.
   * If the original payload is in pprof format, it SHOULD not be included in this field.
   * The field is optional, however if it is present `profile` MUST be present and contain the same profiling information.
   */
  ProtobufCBinaryData original_payload;
  /*
   * This is a reference to a pprof profile. Required, even when original_payload is present.
   */
  Opentelemetry__Proto__Profiles__V1development__Profile *profile;
};
#define OPENTELEMETRY__PROTO__PROFILES__V1DEVELOPMENT__PROFILE_CONTAINER__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&opentelemetry__proto__profiles__v1development__profile_container__descriptor) \
    , {0,NULL}, 0, 0, 0,NULL, 0, (char *)protobuf_c_empty_string, {0,NULL}, NULL }


/* Opentelemetry__Proto__Profiles__V1development__ProfilesData methods */
void   opentelemetry__proto__profiles__v1development__profiles_data__init
                     (Opentelemetry__Proto__Profiles__V1development__ProfilesData         *message);
size_t opentelemetry__proto__profiles__v1development__profiles_data__get_packed_size
                     (const Opentelemetry__Proto__Profiles__V1development__ProfilesData   *message);
size_t opentelemetry__proto__profiles__v1development__profiles_data__pack
                     (const Opentelemetry__Proto__Profiles__V1development__ProfilesData   *message,
                      uint8_t             *out);
size_t opentelemetry__proto__profiles__v1development__profiles_data__pack_to_buffer
                     (const Opentelemetry__Proto__Profiles__V1development__ProfilesData   *message,
                      ProtobufCBuffer     *buffer);
Opentelemetry__Proto__Profiles__V1development__ProfilesData *
       opentelemetry__proto__profiles__v1development__profiles_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   opentelemetry__proto__profiles__v1development__profiles_data__free_unpacked
                     (Opentelemetry__Proto__Profiles__V1development__ProfilesData *message,
                      ProtobufCAllocator *allocator);
/* Opentelemetry__Proto__Profiles__V1development__ResourceProfiles methods */
void   opentelemetry__proto__profiles__v1development__resource_profiles__init
                     (Opentelemetry__Proto__Profiles__V1development__ResourceProfiles         *message);
size_t opentelemetry__proto__profiles__v1development__resource_profiles__get_packed_size
                     (const Opentelemetry__Proto__Profiles__V1development__ResourceProfiles   *message);
size_t opentelemetry__proto__profiles__v1development__resource_profiles__pack
                     (const Opentelemetry__Proto__Profiles__V1development__ResourceProfiles   *message,
                      uint8_t             *out);
size_t opentelemetry__proto__profiles__v1development__resource_profiles__pack_to_buffer
                     (const Opentelemetry__Proto__Profiles__V1development__ResourceProfiles   *message,
                      ProtobufCBuffer     *buffer);
Opentelemetry__Proto__Profiles__V1development__ResourceProfiles *
       opentelemetry__proto__profiles__v1development__resource_profiles__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   opentelemetry__proto__profiles__v1development__resource_profiles__free_unpacked
                     (Opentelemetry__Proto__Profiles__V1development__ResourceProfiles *message,
                      ProtobufCAllocator *allocator);
/* Opentelemetry__Proto__Profiles__V1development__ScopeProfiles methods */
void   opentelemetry__proto__profiles__v1development__scope_profiles__init
                     (Opentelemetry__Proto__Profiles__V1development__ScopeProfiles         *message);
size_t opentelemetry__proto__profiles__v1development__scope_profiles__get_packed_size
                     (const Opentelemetry__Proto__Profiles__V1development__ScopeProfiles   *message);
size_t opentelemetry__proto__profiles__v1development__scope_profiles__pack
                     (const Opentelemetry__Proto__Profiles__V1development__ScopeProfiles   *message,
                      uint8_t             *out);
size_t opentelemetry__proto__profiles__v1development__scope_profiles__pack_to_buffer
                     (const Opentelemetry__Proto__Profiles__V1development__ScopeProfiles   *message,
                      ProtobufCBuffer     *buffer);
Opentelemetry__Proto__Profiles__V1development__ScopeProfiles *
       opentelemetry__proto__profiles__v1development__scope_profiles__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   opentelemetry__proto__profiles__v1development__scope_profiles__free_unpacked
                     (Opentelemetry__Proto__Profiles__V1development__ScopeProfiles *message,
                      ProtobufCAllocator *allocator);
/* Opentelemetry__Proto__Profiles__V1development__ProfileContainer methods */
void   opentelemetry__proto__profiles__v1development__profile_container__init
                     (Opentelemetry__Proto__Profiles__V1development__ProfileContainer         *message);
size_t opentelemetry__proto__profiles__v1development__profile_container__get_packed_size
                     (const Opentelemetry__Proto__Profiles__V1development__ProfileContainer   *message);
size_t opentelemetry__proto__profiles__v1development__profile_container__pack
                     (const Opentelemetry__Proto__Profiles__V1development__ProfileContainer   *message,
                      uint8_t             *out);
size_t opentelemetry__proto__profiles__v1development__profile_container__pack_to_buffer
                     (const Opentelemetry__Proto__Profiles__V1development__ProfileContainer   *message,
                      ProtobufCBuffer     *buffer);
Opentelemetry__Proto__Profiles__V1development__ProfileContainer *
       opentelemetry__proto__profiles__v1development__profile_container__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   opentelemetry__proto__profiles__v1development__profile_container__free_unpacked
                     (Opentelemetry__Proto__Profiles__V1development__ProfileContainer *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Opentelemetry__Proto__Profiles__V1development__ProfilesData_Closure)
                 (const Opentelemetry__Proto__Profiles__V1development__ProfilesData *message,
                  void *closure_data);
typedef void (*Opentelemetry__Proto__Profiles__V1development__ResourceProfiles_Closure)
                 (const Opentelemetry__Proto__Profiles__V1development__ResourceProfiles *message,
                  void *closure_data);
typedef void (*Opentelemetry__Proto__Profiles__V1development__ScopeProfiles_Closure)
                 (const Opentelemetry__Proto__Profiles__V1development__ScopeProfiles *message,
                  void *closure_data);
typedef void (*Opentelemetry__Proto__Profiles__V1development__ProfileContainer_Closure)
                 (const Opentelemetry__Proto__Profiles__V1development__ProfileContainer *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor opentelemetry__proto__profiles__v1development__profiles_data__descriptor;
extern const ProtobufCMessageDescriptor opentelemetry__proto__profiles__v1development__resource_profiles__descriptor;
extern const ProtobufCMessageDescriptor opentelemetry__proto__profiles__v1development__scope_profiles__descriptor;
extern const ProtobufCMessageDescriptor opentelemetry__proto__profiles__v1development__profile_container__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_opentelemetry_2fproto_2fprofiles_2fv1development_2fprofiles_2eproto__INCLUDED */
