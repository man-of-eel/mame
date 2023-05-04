/*

Quick & Crash - Electromechanical light-gun game

CPU: Kawasaki KL5C80A12CFP
RAM: Hitachi 6264BLP10L
Sound: Oki M9810 & 2 speakers, one in gun cabinet, one in target cabinet

Cool Gunman is thought to run on similar hardware, it probably belongs here

*/

#include "emu.h"
#include "cpu/z80/kl5c80a12.h"
#include "machine/i8255.h"
#include "sound/okim9810.h"
#include "speaker.h"

#include "qcrash.lh"

namespace {

class qcrash_state : public driver_device
{
public:
	qcrash_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_oki(*this, "oki")
	{
	}

	void qcrash(machine_config &config);

protected:
	virtual void machine_start() override;

private:
	required_device<kl5c80a12_device> m_maincpu;
	required_device<okim9810_device> m_oki;

	void main_map(address_map &map);
};

void qcrash_state::machine_start()
{
}

static INPUT_PORTS_START(qcrash)
INPUT_PORTS_END

void qcrash_state::main_map(address_map &map)
{
	// Guess
	map(0x0000, 0xf800).rom();
	map(0xf800, 0xffff).ram();
}

void qcrash_state::qcrash(machine_config &config)
{
	KL5C80A12(config, m_maincpu, 20.0000_MHz_XTAL);
	m_maincpu->set_addrmap(AS_PROGRAM, &qcrash_state::main_map);

	I8255(config, "ppi"); // NEC D71055C

	// Sound hardware

	SPEAKER(config, "gun_speaker").front_center(); // Gun cabinet
	SPEAKER(config, "target_speaker").front_center(); // Target cabinet

	okim9810_device &oki(OKIM9810(config, m_oki, XTAL(4'096'000)));

	// May need to be swapped. The announcer should come from gun_speaker
	oki.add_route(0, "gun_speaker", 1.00);
	oki.add_route(1, "target_speaker", 1.00);
}

ROM_START(qcrash)
	ROM_REGION(0x10000, "maincpu",0)
	ROM_LOAD("qc1_mproc.ic3",0x0000,0x10000,CRC(8e3f605d) SHA1(69a0da6286e250b92e47b66c9423bc5c793b350b))

	// Sound roms go here
ROM_END

ROM_START(qcrash3a)
	ROM_REGION(0x10000, "maincpu",0)
	ROM_LOAD("qc3_mpro.ic3",0x0000,0x10000,CRC(42c54dec) SHA1(0f6ca4bec7ae4f60b1943dad756933d02cd660c4))

	// same here
ROM_END

} // anonymous namespace

//    YEAR  NAME       PARENT MACHINE   INPUT     CLASS            INIT        ROT   COMPANY         FULLNAME                      FLAGS
GAMEL(1999, qcrash,    0,     qcrash,   qcrash,   qcrash_state,    empty_init, ROT0, "Namco", "Quick & Crash (English, QC1 V2.200)", MACHINE_IS_SKELETON_MECHANICAL, layout_qcrash)
GAMEL(1999, qcrash3a,   qcrash,     qcrash,   qcrash,   qcrash_state,    empty_init, ROT0, "Namco", "Quick & Crash (English, QC3 unknown 1)", MACHINE_IS_SKELETON_MECHANICAL, layout_qcrash)

