// ==========================================================================
// Dedmonwakeen's Raid DPS/TPS Simulator.
// Send questions to natehieter@gmail.com
// ==========================================================================
#ifndef COVENANT_DATA_HPP
#define COVENANT_DATA_HPP

#include "util/span.hpp"
#include "util/string_view.hpp"

#include "client_data.hpp"

struct conduit_entry_t
{
  unsigned id;
  unsigned spell_id;
  const char* name;

  static const conduit_entry_t& find( util::string_view name, bool ptr, bool tokenized = false );
  static const conduit_entry_t& find( unsigned conduit_id, bool ptr )
  { return dbc::find<conduit_entry_t>( conduit_id, ptr, &conduit_entry_t::id ); }
  static const conduit_entry_t& find_by_spellid( unsigned spell_id, bool ptr );

  static const conduit_entry_t& nil()
  { return dbc::nil<conduit_entry_t>; }

  static util::span<const conduit_entry_t> data( bool ptr );
};

struct conduit_rank_entry_t
{
  unsigned conduit_id;
  unsigned rank;
  unsigned spell_id;
  double   value;

  static util::span<const conduit_rank_entry_t> find( unsigned id, bool ptr )
  { return dbc::find_many<conduit_rank_entry_t>( id, ptr, {}, &conduit_rank_entry_t::conduit_id ); }

  static const conduit_rank_entry_t& find( unsigned id, unsigned rank, bool ptr );

  static const conduit_rank_entry_t& nil()
  { return dbc::nil<conduit_rank_entry_t>; }

  static util::span<const conduit_rank_entry_t> data( bool ptr );
};

struct soulbind_ability_entry_t
{
  unsigned spell_id;
  unsigned covenant_id;
  unsigned soulbind_id;
  const char* name;

  static const soulbind_ability_entry_t& find( util::string_view name, bool ptr, bool tokenized = false );
  static const soulbind_ability_entry_t& find( unsigned spell_id, bool ptr )
  { return dbc::find<soulbind_ability_entry_t>( spell_id, ptr, &soulbind_ability_entry_t::spell_id ); }
  static const soulbind_ability_entry_t& find_by_soulbind_id( unsigned soulbind_id, bool ptr );

  static const soulbind_ability_entry_t& nil()
  { return dbc::nil<soulbind_ability_entry_t>; }

  static util::span<const soulbind_ability_entry_t> data( bool ptr );
};

struct covenant_ability_entry_t
{
  unsigned class_id;
  unsigned covenant_id;
  unsigned ability_type;
  unsigned spell_id;
  const char* name;

  static const covenant_ability_entry_t& find( util::string_view name, bool ptr );
  static const covenant_ability_entry_t& find( unsigned spell_id, bool ptr );

  static const covenant_ability_entry_t& nil()
  { return dbc::nil<covenant_ability_entry_t>; }

  static util::span<const covenant_ability_entry_t> data( bool ptr );
};

struct renown_reward_entry_t
{
  unsigned covenant_id;
  unsigned renown_level;
  unsigned spell_id;
  const char* name;

  static util::span<const renown_reward_entry_t> find_by_covenant_id( unsigned covenant_id, bool ptr )
  { return dbc::find_many<renown_reward_entry_t>( covenant_id, ptr, {}, &renown_reward_entry_t::covenant_id ); }

  static const renown_reward_entry_t& nil()
  { return dbc::nil<renown_reward_entry_t>; }

  static util::span<const renown_reward_entry_t> data( bool ptr );
};

struct enhanced_conduit_entry_t
{
  unsigned soulbind_id;
  unsigned tier;
  unsigned ui_order;
  unsigned renown_level;

  static util::span<const enhanced_conduit_entry_t> find_by_soulbind_id( unsigned soulbind_id, bool ptr )
  { return dbc::find_many<enhanced_conduit_entry_t>( soulbind_id, ptr, {}, &enhanced_conduit_entry_t::soulbind_id ); }

  static const enhanced_conduit_entry_t& nil()
  { return dbc::nil<enhanced_conduit_entry_t>; }

  static util::span<const enhanced_conduit_entry_t> data( bool ptr );
};

#endif /* COVENANT_DATA_HPP */


