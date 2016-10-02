/* Copyright (C) 2016 G.P. Halkes
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 3, as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DEVICE_DB_H_
#define DEVICE_DB_H_

#include <map>
#include <vector>

#include "status.h"
#include "util.h"

struct DeviceInfo {
  std::string name;
  uint16_t device_id = 0;
  uint32_t program_memory_size = 0;
  uint32_t user_id_size = 0;
  uint32_t user_id_offset = 0;
  uint32_t config_size = 0;
  uint32_t config_offset = 0;
  uint32_t eeprom_size = 0;
  uint32_t eeprom_offset = 0;
  uint16_t write_block_size = 0;
  Datastring16 chip_erase_sequence;
  Datastring16 flash_erase_sequence;
  Datastring16 user_id_erase_sequence;
  Datastring16 config_erase_sequence;
  Datastring16 eeprom_erase_sequence;
  Duration bulk_erase_timing = 0;
  Duration block_write_timing = MilliSeconds(1);
  Duration config_write_timing = MilliSeconds(5);
  std::vector<uint32_t> missing_locations;

  void Dump() const;
  Status Validate() const;
};

class DeviceDb {
 public:
  Status Load(const std::string &name);

  Status GetDeviceInfo(uint16_t device_id, DeviceInfo *device_info);

 private:
  std::map<uint16_t, DeviceInfo> device_db_;
};

#endif