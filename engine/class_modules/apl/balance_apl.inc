action_priority_list_t* precombat = get_action_priority_list( "precombat" );
action_priority_list_t* def = get_action_priority_list( "default" );
action_priority_list_t* st = get_action_priority_list( "st" );
action_priority_list_t* aoe = get_action_priority_list( "aoe" );
action_priority_list_t* boat = get_action_priority_list( "boat" );
action_priority_list_t* fallthru = get_action_priority_list( "fallthru" );

precombat->add_action( "variable,name=on_use_trinket,value=0","The variable is set to 0 with no stat on use trinkets, 1 when the first one is on use, 2 if the second is and 3 if both are" );
precombat->add_action( "variable,name=on_use_trinket,op=add,value=trinket.1.has_proc.any&trinket.1.cooldown.duration" );
precombat->add_action( "variable,name=on_use_trinket,op=add,value=(trinket.2.has_proc.any&trinket.2.cooldown.duration)*2" );
precombat->add_action( "moonkin_form" );
precombat->add_action( "wrath","Precast 2 Wrath and a Starsurge on ST with Night Fae and BoAT or Starfire otherwise" );
precombat->add_action( "wrath" );
precombat->add_action( "starfire,if=!runeforge.balance_of_all_things|!covenant.night_fae|!spell_targets.starfall=1|!talent.natures_balance.enabled" );
precombat->add_action( "starsurge,if=runeforge.balance_of_all_things&covenant.night_fae&spell_targets.starfall=1" );

def->add_action( "variable,name=is_aoe,value=spell_targets.starfall>1&(!talent.starlord.enabled|talent.stellar_drift.enabled)|spell_targets.starfall>2","Sets AoE on 3+ without drift and with Starlord and 2+ otherwise" );
def->add_action( "variable,name=is_cleave,value=spell_targets.starfire>1","Sets cleave when Starfire can hit 2+ targets which is relevant for the Eclipse to be preferred and which filler to cast" );
def->add_action( "berserking,if=(!covenant.night_fae|!cooldown.convoke_the_spirits.up)&buff.ca_inc.remains>15","Use Berserking with CA/Inc or after Convoke in CA/Inc" );
def->add_action( "potion,if=buff.ca_inc.remains>15|fight_remains<25","Pot with a CA/Inc that isn't a Pulsar proc or when the fight is about to end" );
def->add_action( "variable,name=convoke_desync,value=ceil((interpolated_fight_remains-15-cooldown.ca_inc.remains)%180)=ceil((interpolated_fight_remains-15-120-cooldown.convoke_the_spirits.remains)%180)&!raid_event.adds.exists|cooldown.ca_inc.remains>interpolated_fight_remains|cooldown.convoke_the_spirits.remains>interpolated_fight_remains-10|!covenant.night_fae","Calculates whether using Convoke now will allow you to still cast the same amount of Convoke+CA/Inc casts" );
def->add_action( "variable,name=cd_condition,value=(target.time_to_die>15|raid_event.adds.in>50)&((!equipped.empyreal_ordnance|cooldown.empyreal_ordnance.remains<160&!cooldown.empyreal_ordnance.ready)&((variable.on_use_trinket=1|variable.on_use_trinket=3)&(trinket.1.ready_cooldown|trinket.1.cooldown.remains>interpolated_fight_remains-10)|variable.on_use_trinket=2&(trinket.2.ready_cooldown|trinket.2.cooldown.remains>interpolated_fight_remains-10)|variable.on_use_trinket=0)|covenant.kyrian)","Used to delay the usage of CA/Inc when using double on use and prevent usage when an add event is about to die" );
def->add_action( "use_item,name=empyreal_ordnance,if=cooldown.ca_inc.remains<20&cooldown.convoke_the_spirits.remains<20|fight_remains<37","Use Empyreal Ordnance 20secs before a CA/Inc use." );
def->add_action( "use_item,name=soulletting_ruby,if=cooldown.ca_inc.remains<6&!variable.convoke_desync|cooldown.convoke_the_spirits.remains<6&variable.convoke_desync|fight_remains<25","Use Soulleting Ruby 6secs before a CA/Inc use." );
def->add_action( "use_item,name=inscrutable_quantum_device,if=buff.ca_inc.remains>15" );
def->add_action( "use_items,slots=trinket1,if=variable.on_use_trinket=2&!trinket.2.ready_cooldown|(variable.on_use_trinket=1|variable.on_use_trinket=3)&(buff.ca_inc.up|cooldown.ca_inc.remains+2>trinket.1.cooldown.duration&(!covenant.night_fae|!variable.convoke_desync)&!covenant.kyrian|covenant.night_fae&variable.convoke_desync&cooldown.convoke_the_spirits.up&!cooldown.ca_inc.up&((buff.eclipse_lunar.remains>10|buff.eclipse_solar.remains>10)&!runeforge.balance_of_all_things|(buff.balance_of_all_things_nature.stack=5|buff.balance_of_all_things_arcane.stack=5))|buff.kindred_empowerment_energize.up)|fight_remains<20|variable.on_use_trinket=0","This is a rather elaborate way to make all on use stat trinkets to be lined up with CA/Inc and Convoke and use the 2nd slot on cd if both trinkets are on use stat trinkets" );
def->add_action( "use_items,slots=trinket2,if=variable.on_use_trinket!=2&!trinket.1.ready_cooldown|variable.on_use_trinket=2&(buff.ca_inc.up|cooldown.ca_inc.remains+2>trinket.2.cooldown.duration&(!covenant.night_fae|!variable.convoke_desync)&!covenant.kyrian|covenant.night_fae&variable.convoke_desync&cooldown.convoke_the_spirits.up&!cooldown.ca_inc.up&((buff.eclipse_lunar.remains>10|buff.eclipse_solar.remains>10)&!runeforge.balance_of_all_things|(buff.balance_of_all_things_nature.stack=5|buff.balance_of_all_things_arcane.stack=5)))|buff.kindred_empowerment_energize.up|fight_remains<20|variable.on_use_trinket=0" );
def->add_action( "use_items","Uses all other on use items on cd" );
def->add_action( "run_action_list,name=aoe,if=variable.is_aoe","Decide action list based on situation/legis" );
def->add_action( "run_action_list,name=boat,if=runeforge.balance_of_all_things.equipped" );
def->add_action( "run_action_list,name=st" );

st->add_action( "ravenous_frenzy,if=buff.ca_inc.remains>15","Use the Venthyr with a CA/Inc that isn't from Pulsar" );
st->add_action( "starsurge,if=runeforge.timeworn_dreambinder.equipped&(eclipse.in_any&!((buff.timeworn_dreambinder.remains>action.wrath.execute_time+0.1&(eclipse.in_both|eclipse.in_solar|eclipse.lunar_next)|buff.timeworn_dreambinder.remains>action.starfire.execute_time+0.1&(eclipse.in_lunar|eclipse.solar_next|eclipse.any_next))|!buff.timeworn_dreambinder.up)|(buff.ca_inc.up|variable.convoke_desync)&cooldown.convoke_the_spirits.ready&covenant.night_fae)&(!covenant.kyrian|cooldown.empower_bond.remains>8)&(buff.ca_inc.up|!cooldown.ca_inc.ready)","Use Starsurge to keep up the Dreambinder buff if it would expire before finishing the next cast or to dump before Convoke" );
st->add_action( "adaptive_swarm,target_if=!dot.adaptive_swarm_damage.ticking&!action.adaptive_swarm_damage.in_flight&(!dot.adaptive_swarm_heal.ticking|dot.adaptive_swarm_heal.remains>5)|dot.adaptive_swarm_damage.stack<3&dot.adaptive_swarm_damage.remains<3&dot.adaptive_swarm_damage.ticking","Use Adaptive Swarm when there is no active swarm, as late as possible on swarm with 2 or fewer stacks or on a 3+ swarm so that the new swarm arrives just after that swarm expires" );
st->add_action( "convoke_the_spirits,if=!druid.no_cds&((variable.convoke_desync&!cooldown.ca_inc.ready&!runeforge.primordial_arcanic_pulsar|buff.ca_inc.up)&astral_power<40&(buff.eclipse_lunar.remains>10|buff.eclipse_solar.remains>10)|fight_remains<10&!cooldown.ca_inc.ready)","Uses Convoke if CA/Inc is up or you are desyncing CA/Inc with Convoke and you are below 40 AsP" );
st->add_action( "variable,name=dot_requirements,value=(buff.ravenous_frenzy.remains>5|!buff.ravenous_frenzy.up)&(buff.kindred_empowerment_energize.remains<gcd.max)&(buff.eclipse_solar.remains>gcd.max|buff.eclipse_lunar.remains>gcd.max)","Condition for all dots that makes sure they aren't refreshed when Ravenous Frenzy has less than 5 secs remaining or the kyrian buff is about to fall off or any Eclipse is about to expire" );
st->add_action( "moonfire,target_if=refreshable&target.time_to_die>12,if=ap_check&variable.dot_requirements" );
st->add_action( "sunfire,target_if=refreshable&target.time_to_die>12,if=ap_check&variable.dot_requirements" );
st->add_action( "stellar_flare,target_if=refreshable&target.time_to_die>16,if=ap_check&variable.dot_requirements" );
st->add_action( "force_of_nature,if=ap_check","Use FoN on cd without capping" );
st->add_action( "kindred_spirits,if=((buff.eclipse_solar.remains>10|buff.eclipse_lunar.remains>10)&cooldown.ca_inc.remains>30&(buff.primordial_arcanic_pulsar.value<240|!runeforge.primordial_arcanic_pulsar.equipped))|buff.primordial_arcanic_pulsar.value>=270|cooldown.ca_inc.ready&astral_power>90","Use Kindred Spirits with any long enough lasting Eclipse and try to line it up with Pulsar and CA/Inc" );
st->add_action( "celestial_alignment,if=!druid.no_cds&variable.cd_condition&(astral_power>90&(buff.kindred_empowerment_energize.up|!covenant.kyrian)|covenant.night_fae|buff.bloodlust.up&buff.bloodlust.remains<20+((9*runeforge.primordial_arcanic_pulsar.equipped)+(conduit.precise_alignment.time_value)))&!buff.ca_inc.up&(!covenant.night_fae|cooldown.convoke_the_spirits.up|interpolated_fight_remains<cooldown.convoke_the_spirits.remains+6|interpolated_fight_remains%%180<20+(conduit.precise_alignment.time_value))","Use CA/Inc with Convoke/Kindred Spirits and don't overwrite Pulsar or when Bloodlust would expire before CA/Inc expires" );
st->add_action( "incarnation,if=!druid.no_cds&variable.cd_condition&(astral_power>90&(buff.kindred_empowerment_energize.up|!covenant.kyrian)|covenant.night_fae|buff.bloodlust.up&buff.bloodlust.remains<30+((9*runeforge.primordial_arcanic_pulsar.equipped)+(conduit.precise_alignment.time_value)))&!buff.ca_inc.up&(!covenant.night_fae|cooldown.convoke_the_spirits.up|interpolated_fight_remains<cooldown.convoke_the_spirits.remains+6|interpolated_fight_remains%%180<30+(conduit.precise_alignment.time_value))" );
st->add_action( "variable,name=save_for_ca_inc,value=!cooldown.ca_inc.ready|!variable.convoke_desync&covenant.night_fae|druid.no_cds","Variable used on abilities that want to be saved for CA/Inc so that they arent wasted just before them" );
st->add_action( "fury_of_elune,if=eclipse.in_any&ap_check&buff.primordial_arcanic_pulsar.value<240&(dot.adaptive_swarm_damage.ticking|!covenant.necrolord)&variable.save_for_ca_inc","Uses FoE if in an Eclipse and tries to line it up with Pulsar, CA/Inc and Adaptive Swarm" );
st->add_action( "starfall,if=buff.oneths_perception.up&buff.starfall.refreshable","Use Oneth Starfall procs if Starfall isn't up" );
st->add_action( "cancel_buff,name=starlord,if=buff.starlord.remains<5&(buff.eclipse_solar.remains>5|buff.eclipse_lunar.remains>5)&astral_power>90" );
st->add_action( "starsurge,if=covenant.night_fae&variable.convoke_desync&cooldown.convoke_the_spirits.remains<5&!druid.no_cds","Dumps AsP before Convoke using the Convoke condition to check if Convoke is actually about to be cast" );
st->add_action( "starfall,if=talent.stellar_drift.enabled&!talent.starlord.enabled&buff.starfall.refreshable&(buff.eclipse_lunar.remains>6&eclipse.in_lunar&buff.primordial_arcanic_pulsar.value<250|buff.primordial_arcanic_pulsar.value>=250&astral_power>90|dot.adaptive_swarm_damage.remains>8|action.adaptive_swarm_damage.in_flight)&!cooldown.ca_inc.ready","Use Starfall with Stellar Drift and no Starlord, when no Starfall is up, you are in Lunar Eclipse or to proc Pulsar when above 90 AsP or adpative swarm has 8+secs remaining or is in flight" );
st->add_action( "starsurge,if=buff.oneths_clear_vision.up|buff.kindred_empowerment_energize.up|buff.ca_inc.up&(buff.ravenous_frenzy.remains<gcd.max*ceil(astral_power%30)&buff.ravenous_frenzy.up|!buff.ravenous_frenzy.up&!cooldown.ravenous_frenzy.ready|!covenant.venthyr)|astral_power>90&eclipse.in_any","Use Starsurge Oneth procs and dump AsP when CA/Inc or the Venthyr buff is about to fall off or you'd cap AsP" );
st->add_action( "starsurge,if=talent.starlord.enabled&!runeforge.timeworn_dreambinder.equipped&(buff.starlord.up|astral_power>90)&buff.starlord.stack<3&(buff.eclipse_solar.up|buff.eclipse_lunar.up)&buff.primordial_arcanic_pulsar.value<270&(cooldown.ca_inc.remains>10|!variable.convoke_desync&covenant.night_fae)","Try to make the best of Starlord by stacking it up quickly in any Eclipse but Pulsar isnt about to be procced" );
st->add_action( "starsurge,if=!runeforge.timeworn_dreambinder.equipped&(buff.primordial_arcanic_pulsar.value<270|buff.primordial_arcanic_pulsar.value<250&talent.stellar_drift.enabled)&buff.eclipse_solar.remains>7&eclipse.in_solar&!buff.oneths_perception.up&!talent.starlord.enabled&cooldown.ca_inc.remains>7&(cooldown.kindred_spirits.remains>7|!covenant.kyrian)","Dump Starsurge in a 7+sec Solar Eclipse, don't let it proc Pulsar (that is handled by either the Starfall line or the AsP>90 line for Starsurge), don't overwrite an Oneth proc and let the above line handle Starlord" );
st->add_action( "new_moon,if=(buff.eclipse_lunar.remains>execute_time|(charges=2&recharge_time<5)|charges=3)&ap_check&variable.save_for_ca_inc","Use Moons in Lunar Eclipse and save Half+Full Moon for CA/Inc and Kindred Empowerment" );
st->add_action( "half_moon,if=(buff.eclipse_lunar.remains>execute_time&!covenant.kyrian|(buff.kindred_empowerment_energize.up&covenant.kyrian)|(charges=2&recharge_time<5)|charges=3|buff.ca_inc.up)&ap_check&variable.save_for_ca_inc" );
st->add_action( "full_moon,if=(buff.eclipse_lunar.remains>execute_time&!covenant.kyrian|(buff.kindred_empowerment_energize.up&covenant.kyrian)|(charges=2&recharge_time<5)|charges=3|buff.ca_inc.up)&ap_check&variable.save_for_ca_inc" );
st->add_action( "warrior_of_elune","Use WoE on cd" );
st->add_action( "starfire,if=eclipse.in_lunar|eclipse.solar_next|eclipse.any_next|buff.warrior_of_elune.up&buff.eclipse_lunar.up|(buff.ca_inc.remains<action.wrath.execute_time&buff.ca_inc.up)","Use Starfire to proc Solar Eclipse, CA/Inc has less time than a Wrath execute left or only Lunar Eclipse is up" );
st->add_action( "wrath","Use Wrath otherwise which is in Solar Eclipse, CA/Inc or to proc Lunar Eclipse" );
st->add_action( "run_action_list,name=fallthru","Fallthru" );

aoe->add_action( "variable,name=dream_will_fall_off,value=(buff.timeworn_dreambinder.remains<gcd.max+0.1|buff.timeworn_dreambinder.remains<action.starfire.execute_time+0.1&(eclipse.in_lunar|eclipse.solar_next|eclipse.any_next))&buff.timeworn_dreambinder.up&runeforge.timeworn_dreambinder.equipped","Calculates whether the Dreamcatcher buff will fall off within the next cast" );
aoe->add_action( "variable,name=ignore_starsurge,value=!eclipse.in_solar&(spell_targets.starfire>5&talent.soul_of_the_forest.enabled|spell_targets.starfire>7)","Calculates whether Starsurge is worth casting over Starfire in Lunar Eclipse" );
aoe->add_action( "convoke_the_spirits,if=!druid.no_cds&((variable.convoke_desync&!cooldown.ca_inc.ready|buff.ca_inc.up)&(astral_power<50|variable.ignore_starsurge)&(buff.eclipse_lunar.remains>6|buff.eclipse_solar.remains>6)&(!runeforge.balance_of_all_things|buff.balance_of_all_things_nature.stack>3|buff.balance_of_all_things_arcane.stack>3)|fight_remains<10&!cooldown.ca_inc.ready)","Use Convoke when at less than 50 AsP and line up with CA/Inc" );
aoe->add_action( "ravenous_frenzy,if=buff.ca_inc.remains>15","Use Frenzy with CA/Inc" );
aoe->add_action( "sunfire,target_if=(refreshable|buff.eclipse_solar.remains<3&eclipse.in_solar&remains<14&talent.soul_of_the_forest.enabled)&target.time_to_die>14-spell_targets+remains&(eclipse.in_any|remains<gcd.max),if=","Use Sunfire in pandemic on anything that lives 14secs and less with more targets and at the end of a Solar Eclipse at 14 secs or less remaining as to not having to refresh during Lunar Eclipse" );
aoe->add_action( "starfall,if=(buff.starfall.refreshable&(spell_targets.starfall<3|!runeforge.timeworn_dreambinder.equipped)|talent.soul_of_the_forest.enabled&buff.eclipse_solar.remains<3&eclipse.in_solar&buff.starfall.remains<7&spell_targets.starfall>=4)&(!runeforge.lycaras_fleeting_glimpse.equipped|time%%45>buff.starfall.remains+2)&target.time_to_die>5","Keep up Starfall at all times unless using Lycaras and it is about to proc or let the special action line below handle Dreambinder on 2 targets" );
aoe->add_action( "starfall,if=runeforge.timeworn_dreambinder.equipped&spell_targets.starfall>=3&(!buff.timeworn_dreambinder.up&buff.starfall.refreshable|(variable.dream_will_fall_off&(buff.starfall.remains<3|spell_targets.starfall>2&talent.stellar_drift.enabled&buff.starfall.remains<5)))","With Dreambinder use Starfall to keep up the buff by also using Starfall on 5 seconds or less remaining" );
aoe->add_action( "variable,name=starfall_wont_fall_off,value=astral_power>80-(10*buff.timeworn_dreambinder.stack)-(buff.starfall.remains*3%spell_haste)-(dot.fury_of_elune.remains*5)&buff.starfall.up","Calculates whether a Starsurge use will cause Starfall to fall off, and use Starsurge to keep Dreambinder stack up" );
aoe->add_action( "starsurge,if=variable.dream_will_fall_off&variable.starfall_wont_fall_off&!variable.ignore_starsurge|(buff.balance_of_all_things_nature.stack>3|buff.balance_of_all_things_arcane.stack>3)&spell_targets.starfall<4&variable.starfall_wont_fall_off","Use Starsurge with Dreambinder to keep up the buff without losing Starfall uptime and use Starsurge on 4+ BoAT stacks until 4 targets" );
aoe->add_action( "adaptive_swarm,target_if=!ticking&!action.adaptive_swarm_damage.in_flight|dot.adaptive_swarm_damage.stack<3&dot.adaptive_swarm_damage.remains<3","Use swarm so that you get max uptime by using it as late as possible on less than 3 stacks or just when 3+ stacks expire" );
aoe->add_action( "moonfire,target_if=refreshable&target.time_to_die>((14+(spell_targets.starfire*2*buff.eclipse_lunar.up))+remains)%(1+talent.twin_moons.enabled),if=(cooldown.ca_inc.ready&!druid.no_cds&(variable.convoke_desync|cooldown.convoke_the_spirits.ready|!covenant.night_fae)|spell_targets.starfire<((6-(buff.eclipse_lunar.up*2))*(1+talent.twin_moons.enabled))&!eclipse.solar_next|(eclipse.in_solar|(eclipse.in_both|eclipse.in_lunar)&!talent.soul_of_the_forest.enabled|buff.primordial_arcanic_pulsar.value>=250)&(spell_targets.starfire<10*(1+talent.twin_moons.enabled))&astral_power>50-buff.starfall.remains*6)&(!buff.kindred_empowerment_energize.up|eclipse.in_solar|!covenant.kyrian)","Refresh Moonfire if CA/Inc is ready, there are less than 5 targets in Lunar Eclipse with SotF, less than 10 otherwise in any Eclipse or up to 5 targets before a Lunar Eclipse. Don't refresh during Kindred Empowerment unless in Solar Eclipse" );
aoe->add_action( "force_of_nature,if=ap_check","Use FoN on cd without capping" );
aoe->add_action( "celestial_alignment,if=!druid.no_cds&variable.cd_condition&(buff.starfall.up|astral_power>50)&(!buff.solstice.up&!buff.ca_inc.up&(!covenant.night_fae|cooldown.convoke_the_spirits.up&astral_power<50)&target.time_to_die>15+conduit.precise_alignment.time_value|interpolated_fight_remains<20+conduit.precise_alignment.time_value)","Use CA/Inc on cd unless and line it up with Convoke" );
aoe->add_action( "incarnation,if=!druid.no_cds&variable.cd_condition&(buff.starfall.up|astral_power>50)&(!buff.solstice.up&!buff.ca_inc.up&(!covenant.night_fae|cooldown.convoke_the_spirits.up&astral_power<50)&target.time_to_die>20+conduit.precise_alignment.time_value|interpolated_fight_remains<30+conduit.precise_alignment.time_value)" );
aoe->add_action( "kindred_spirits,if=interpolated_fight_remains<15|(buff.primordial_arcanic_pulsar.value<250|buff.primordial_arcanic_pulsar.value>=250)&buff.starfall.up&(cooldown.ca_inc.remains>50|druid.no_cds)","Use Kindred Spirits on cd with Starfall up and save for Pulsar and CA/Inc" );
aoe->add_action( "stellar_flare,target_if=refreshable&time_to_die>15,if=spell_targets.starfire<4&ap_check&(buff.ca_inc.remains>10|!buff.ca_inc.up)","Refresh flare on up to 3 targets without CA/Inc being about to expire and not overcapping" );
aoe->add_action( "fury_of_elune,if=eclipse.in_any&ap_check&buff.primordial_arcanic_pulsar.value<250&(dot.adaptive_swarm_damage.ticking|!covenant.necrolord|spell_targets>2)","Use FoE if inside an Eclipse and line it up with a Pulsar proc and Adaptive Swarm" );
aoe->add_action( "starfall,if=buff.oneths_perception.up&(buff.starfall.refreshable|astral_power>90)","Use a Starfall Oneth proc unless Starfall is already up or you are about to overcap AsP" );
aoe->add_action( "starfall,if=covenant.night_fae&(variable.convoke_desync|cooldown.ca_inc.up|buff.ca_inc.up)&cooldown.convoke_the_spirits.remains<gcd.max*ceil(astral_power%50)&buff.starfall.remains<4&!druid.no_cds","Dump AsP before Convoke with Starfall and then Starsurge" );
aoe->add_action( "starsurge,if=covenant.night_fae&(variable.convoke_desync|cooldown.ca_inc.up|buff.ca_inc.up)&cooldown.convoke_the_spirits.remains<6&buff.starfall.up&eclipse.in_any&!variable.ignore_starsurge&!druid.no_cds" );
aoe->add_action( "starsurge,if=buff.oneths_clear_vision.up|(!starfire.ap_check&!variable.ignore_starsurge|(buff.ca_inc.remains<5&buff.ca_inc.up|(buff.ravenous_frenzy.remains<gcd.max*ceil(astral_power%30)&buff.ravenous_frenzy.up))&variable.starfall_wont_fall_off&spell_targets.starfall<3)&(!runeforge.timeworn_dreambinder.equipped|spell_targets.starfall<3)","Use Starsurge with an Oneth proc or if you'd overcap AsP with your next cast. Also dumps AsP at the end of the Venthyr buff if Starfall wouldn't fall off on 4 or less targets" );
aoe->add_action( "new_moon,if=(buff.eclipse_solar.remains>execute_time|(charges=2&recharge_time<5)|charges=3)&ap_check","Use Moons in Solar Eclipse and save Full Moon for CA/Inc" );
aoe->add_action( "half_moon,if=(buff.eclipse_solar.remains>execute_time|(charges=2&recharge_time<5)|charges=3)&ap_check" );
aoe->add_action( "full_moon,if=(buff.eclipse_solar.remains>execute_time&(cooldown.ca_inc.remains>50|cooldown.convoke_the_spirits.remains>50)|(charges=2&recharge_time<5)|charges=3)&ap_check" );
aoe->add_action( "warrior_of_elune","Use WoE on CD" );
aoe->add_action( "variable,name=starfire_in_solar,value=spell_targets.starfire>4+floor(mastery_value*100%20)+floor(buff.starsurge_empowerment_solar.stack%4)","Calculates whether to use Starfire in Solar which is at 5 targets+1 for every 20% mastery or 4 Starsurge Empowerment stacks" );
aoe->add_action( "wrath,if=(eclipse.lunar_next|eclipse.any_next&variable.is_cleave)&(target.time_to_die>4|eclipse.lunar_in_2|fight_remains<10)|buff.eclipse_solar.remains<action.starfire.execute_time&buff.eclipse_solar.up|eclipse.in_solar&!variable.starfire_in_solar|buff.ca_inc.remains<action.starfire.execute_time&!variable.is_cleave&buff.ca_inc.remains<execute_time&buff.ca_inc.up|buff.ravenous_frenzy.up&spell_haste>0.6&(spell_targets<=3|!talent.soul_of_the_forest.enabled)|!variable.is_cleave&buff.ca_inc.remains>execute_time","Use Wrath in Solar Eclipse or if no Starfire will fit into CA/Inc anymore" );
aoe->add_action( "starfire","Use Starfire if in Lunar Eclipse, in Solar Eclipse on 4+ targets or to proc Solar Eclipse" );
aoe->add_action( "run_action_list,name=fallthru","Fallthru" );

boat->add_action( "ravenous_frenzy,if=buff.ca_inc.remains>15","Frenzy with CA/Inc" );
boat->add_action( "variable,name=critnotup,value=!buff.balance_of_all_things_nature.up&!buff.balance_of_all_things_arcane.up","Checks if the BoAT crit buff is not up for later use" );
boat->add_action( "adaptive_swarm,target_if=buff.balance_of_all_things_nature.stack<4&buff.balance_of_all_things_arcane.stack<4&(!dot.adaptive_swarm_damage.ticking&!action.adaptive_swarm_damage.in_flight&(!dot.adaptive_swarm_heal.ticking|dot.adaptive_swarm_heal.remains>3)|dot.adaptive_swarm_damage.stack<3&dot.adaptive_swarm_damage.remains<5&dot.adaptive_swarm_damage.ticking)","Use Adaptive Swarm when at less than 4 BoAT stacks and to refresh a <=2 stack as late as possible or time it so it arrives just after a 3+ stack expires" );
boat->add_action( "convoke_the_spirits,if=!druid.no_cds&((variable.convoke_desync&!cooldown.ca_inc.ready|buff.ca_inc.up)&(buff.balance_of_all_things_nature.stack=5|buff.balance_of_all_things_arcane.stack=5)|fight_remains<10)","Use Convoke with CA/Inc when possible and otherwise with a BoAT buff when desyncing" );
boat->add_action( "fury_of_elune,if=((buff.balance_of_all_things_nature.stack>4|buff.balance_of_all_things_arcane.stack>4)&(druid.no_cds|cooldown.ca_inc.remains>50|(covenant.night_fae&cooldown.convoke_the_spirits.remains>50)))|(dot.adaptive_swarm_damage.remains>8&cooldown.ca_inc.remains>10&covenant.necrolord)|interpolated_fight_remains<8&!cooldown.ca_inc.ready|(covenant.kyrian&buff.kindred_empowerment.up)","FoE as the first gcd in the a BoAT window or with the Kyrian buff or with a 8+sec Adaptive Swarm and wait for CA/Inc if it wont be up again before the cd is finished" );
boat->add_action( "cancel_buff,name=starlord,if=(buff.balance_of_all_things_nature.remains>4.5|buff.balance_of_all_things_arcane.remains>4.5)&(cooldown.ca_inc.remains>7|(cooldown.empower_bond.remains>7&!buff.kindred_empowerment_energize.up&covenant.kyrian))&astral_power>=30","Cancel Starlord with a new BoAT buff and CA/Inc isn't about to be used" );
boat->add_action( "starsurge,if=!variable.critnotup&(covenant.night_fae|cooldown.ca_inc.remains>7|!variable.cd_condition&!covenant.kyrian|(cooldown.empower_bond.remains>7&!buff.kindred_empowerment_energize.up&covenant.kyrian))&(!dot.fury_of_elune.ticking|!cooldown.ca_inc.ready|!cooldown.convoke_the_spirits.ready)","Dump Starsurges with a BoAT buff but not when pooling for CA/Inc or Kindred Spirits" );
boat->add_action( "starsurge,if=(cooldown.convoke_the_spirits.remains<5&!druid.no_cds&(variable.convoke_desync|cooldown.ca_inc.remains<5)&variable.cd_condition)&!dot.fury_of_elune.ticking&covenant.night_fae&!druid.no_cds&eclipse.in_any","Dump Starsurges before Convoke" );
boat->add_action( "variable,name=dot_requirements,value=(buff.ravenous_frenzy.remains>5|!buff.ravenous_frenzy.up)&(buff.kindred_empowerment_energize.remains<gcd.max)&(buff.eclipse_solar.remains>gcd.max|buff.eclipse_lunar.remains>gcd.max)","Don't dot during the end of Ravenous Frenzy, during kindred empowerment or in the last gcd of an Eclipse" );
boat->add_action( "sunfire,target_if=refreshable&target.time_to_die>16,if=ap_check&variable.dot_requirements" );
boat->add_action( "moonfire,target_if=refreshable&target.time_to_die>13.5,if=ap_check&variable.dot_requirements" );
boat->add_action( "stellar_flare,target_if=refreshable&target.time_to_die>16+remains,if=ap_check&variable.dot_requirements" );
boat->add_action( "force_of_nature,if=ap_check","FoN on cd without capping" );
boat->add_action( "kindred_spirits,if=(eclipse.lunar_next|eclipse.solar_next|eclipse.any_next|buff.balance_of_all_things_nature.remains>4.5|buff.balance_of_all_things_arcane.remains>4.5|astral_power>90&cooldown.ca_inc.ready&!druid.no_cds)&(cooldown.ca_inc.remains>30|cooldown.ca_inc.ready)|interpolated_fight_remains<10","Kindred Spirits when about to enter a new BoAT window and save for CA/Inc" );
boat->add_action( "fury_of_elune,if=cooldown.ca_inc.ready&variable.cd_condition&(astral_power>90&!covenant.night_fae|covenant.night_fae&astral_power<40)&(!covenant.night_fae|cooldown.convoke_the_spirits.ready)&!druid.no_cds","FoE right before using CA" );
boat->add_action( "celestial_alignment,if=!druid.no_cds&variable.cd_condition&((astral_power>90&(buff.kindred_empowerment_energize.up|!covenant.kyrian)|buff.bloodlust.up&buff.bloodlust.remains<20+(conduit.precise_alignment.time_value))|interpolated_fight_remains<20+(conduit.precise_alignment.time_value)|covenant.night_fae)&(!covenant.night_fae|(astral_power<40|dot.fury_of_elune.ticking)&(variable.convoke_desync|cooldown.convoke_the_spirits.ready))","CA/Inc when at 90+ AsP (orlower than 40 AsP with Convoke) without losing time in Bloodlust and line up with Convoke if it was desynced" );
boat->add_action( "incarnation,if=!druid.no_cds&variable.cd_condition&((astral_power>90&(buff.kindred_empowerment_energize.up|!covenant.kyrian)|buff.bloodlust.up&buff.bloodlust.remains<30+(conduit.precise_alignment.time_value))|interpolated_fight_remains<30+(conduit.precise_alignment.time_value)|covenant.night_fae)&(!covenant.night_fae|(astral_power<40|dot.fury_of_elune.ticking)&(variable.convoke_desync|cooldown.convoke_the_spirits.ready))" );
boat->add_action( "variable,name=aspPerSec,value=eclipse.in_lunar*8%action.starfire.execute_time+!eclipse.in_lunar*(6+talent.soul_of_the_forest.enabled*3)%action.wrath.execute_time+0.2%spell_haste","Estimates how much AsP are gained per second" );
boat->add_action( "starsurge,if=(interpolated_fight_remains<4|(buff.ravenous_frenzy.remains<gcd.max*ceil(astral_power%30)&buff.ravenous_frenzy.up))|(astral_power+variable.aspPerSec*buff.eclipse_solar.remains+dot.fury_of_elune.ticks_remain*2.5>110|astral_power+variable.aspPerSec*buff.eclipse_lunar.remains+dot.fury_of_elune.ticks_remain*2.5>110)&eclipse.in_any&(!buff.ca_inc.up|!talent.starlord.enabled)&((!cooldown.ca_inc.up|covenant.kyrian&!cooldown.empower_bond.up)|covenant.night_fae)&(!covenant.venthyr|!buff.ca_inc.up|astral_power>90)|(talent.starlord.enabled&buff.ca_inc.up&(buff.starlord.stack<3|astral_power>90))|buff.ca_inc.up&!buff.ravenous_frenzy.up&!talent.starlord.enabled","Dump Starsurges when the fight is about to end, frenzy is about to end, you are at 90+ AsP in an Eclipse, CA/Inc lasts another 8+secs or you would overcap more than ~10 AsP when you wouldn't Starsurge now" );
boat->add_action( "new_moon,if=(buff.eclipse_lunar.remains>execute_time|(charges=2&recharge_time<5)|charges=3)&ap_check","Use Moons in Lunar Eclipse and save Half+Full Moon for CA/Inc" );
boat->add_action( "half_moon,if=(buff.eclipse_lunar.remains>execute_time&(cooldown.ca_inc.remains>50|cooldown.convoke_the_spirits.remains>50)|(charges=2&recharge_time<5)|charges=3)&ap_check" );
boat->add_action( "full_moon,if=(buff.eclipse_lunar.remains>execute_time&(cooldown.ca_inc.remains>50|cooldown.convoke_the_spirits.remains>50)|(charges=2&recharge_time<5)|charges=3)&ap_check" );
boat->add_action( "warrior_of_elune","WoE on cd" );
boat->add_action( "starfire,if=eclipse.in_lunar|eclipse.solar_next|eclipse.any_next|buff.warrior_of_elune.up&buff.eclipse_lunar.up|(buff.ca_inc.remains<action.wrath.execute_time&buff.ca_inc.up)","Use Starfire to proc Solar Eclipse or when in only Lunar Eclipse and use WoE procs if in Lunar Eclipse" );
boat->add_action( "wrath" );
boat->add_action( "run_action_list,name=fallthru" );

fallthru->add_action( "starsurge,if=!runeforge.balance_of_all_things.equipped","Starsurge for movement unless using BoAT" );
fallthru->add_action( "sunfire,target_if=dot.moonfire.remains>remains*22%18","Cast the dot with the most time to add until the max duration is hit. Sunfire remains multiplied to match moonfire duration" );
fallthru->add_action( "moonfire" );