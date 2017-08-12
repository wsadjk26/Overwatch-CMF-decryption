#include <cstdint>

struct CMFHeader
{
  uint32_t m_buildVersion;
  uint32_t m_unk01;
  int32_t m_dataCount;
  uint32_t m_unk02;
  int32_t m_entriesCount;
  // 0x14666D63 '\x14fmc' -> Not Encrypted
  // 0x636D6614 'cmf\x14' -> Encrypted
  uint32_t m_magicbytes;
};

void GenerateKey(uint8_t* buffer, const CMFHeader* header, const int32_t length)
{
  uint32_t kidx = length * header->m_buildVersion;
  for (int32_t i = 0; i != length; ++i)
  {
    buffer[i] = m_keytable[kidx % 512];
    kidx += 3;
  }
}

void GenerateIV(uint8_t* buffer, const CMFHeader* header, const std::string& name, const int32_t length)
{
  SHA1 sha;
  //SHA1 of whateverthemanifestnameis.cmf
  uint8_t digest[SHA1::DIGESTSIZE];
  sha.Update(reinterpret_cast<const uint8_t*>(name.c_str()), name.size());
  sha.Final(digest);
  
  uint32_t kidx = length * header->m_buildVersion;
  uint32_t increment = header->m_entriesCount + digest[header->m_entriesCount % SHA1::DIGESTSIZE];
  for (int32_t i = 0; i != length; ++i)
  {
    //buffer[i] = m_keytable[kidx % 512];
    kidx += increment;
    buffer[i] = digest[kidx % SHA1::DIGESTSIZE];
  }
}

uint8_t m_keytable[512] 
{
  0xDE, 0xC2, 0xB8, 0x91, 0x1E, 0xFA, 0x66, 0xCB, 0xE9, 0x45, 0x0A, 0xF6, 0x0E, 0x6F, 0x9A, 0xF3,
  0x41, 0xEC, 0xA6, 0xC7, 0x84, 0x05, 0x5B, 0xD3, 0x6B, 0x7B, 0x4C, 0xA4, 0x55, 0x18, 0x26, 0xF3,
  0xBA, 0xA8, 0x41, 0x9A, 0x7E, 0xAA, 0x99, 0xE3, 0xA4, 0x11, 0x31, 0xED, 0x3A, 0xDF, 0x44, 0xCC,
  0x28, 0x3C, 0xB7, 0xFE, 0x95, 0x4F, 0xCD, 0xA9, 0x66, 0x7E, 0x58, 0x11, 0x99, 0xC8, 0x25, 0x93,
  0x3E, 0xD0, 0xCF, 0x9B, 0xEA, 0xF2, 0xB1, 0x1E, 0x69, 0x4A, 0x72, 0x73, 0xDD, 0x4D, 0x39, 0x56,
  0xD4, 0x25, 0x88, 0x66, 0x2F, 0x41, 0x1C, 0x93, 0x50, 0x3C, 0x06, 0x80, 0xB0, 0x16, 0xB1, 0x10,
  0xE8, 0xFD, 0xE2, 0x6A, 0xC7, 0xFE, 0x51, 0x38, 0x54, 0xBD, 0xF3, 0x5A, 0x61, 0xBB, 0xF1, 0x7E,
  0x5B, 0x73, 0x9E, 0xB7, 0x79, 0xFB, 0xAC, 0x44, 0x01, 0xD0, 0x59, 0x90, 0xB5, 0xE0, 0xAD, 0xC0,
  0x71, 0x52, 0x5C, 0x3C, 0xCF, 0x6E, 0xD6, 0x46, 0x0B, 0xE9, 0x15, 0x8C, 0xD6, 0x44, 0xB6, 0x40,
  0x8A, 0xFB, 0x37, 0x9D, 0x7E, 0x81, 0x00, 0x03, 0xB3, 0x66, 0x08, 0x60, 0xB2, 0xDC, 0x93, 0x8F,
  0x39, 0x13, 0x62, 0xAE, 0xBB, 0x33, 0x59, 0xA3, 0xD3, 0xAE, 0x1C, 0x23, 0xDB, 0x17, 0x04, 0xC2,
  0x84, 0x64, 0xF0, 0x1A, 0xF7, 0x7C, 0x0F, 0xA1, 0x73, 0xEE, 0x9B, 0x72, 0x42, 0x50, 0x13, 0x1C,
  0xC0, 0xEC, 0x01, 0x99, 0x5B, 0xE4, 0x50, 0x6A, 0x80, 0x1F, 0x8D, 0xAB, 0x1F, 0x15, 0xB1, 0x86,
  0x45, 0x12, 0x0B, 0x3D, 0xD0, 0x73, 0xD8, 0xF4, 0xC0, 0x83, 0x66, 0x4E, 0xD6, 0xD8, 0xEE, 0xA1,
  0xAB, 0xB2, 0x28, 0xAA, 0x77, 0xC1, 0xDC, 0x8D, 0x12, 0x98, 0x1A, 0x5D, 0x54, 0x69, 0x60, 0x6F,
  0x95, 0x99, 0x21, 0x39, 0xD5, 0xDC, 0xDD, 0xF4, 0x2C, 0x38, 0xE0, 0xD6, 0x30, 0x71, 0x1C, 0xEF,
  0x07, 0x9E, 0xF8, 0x51, 0xBB, 0x0F, 0x0E, 0x46, 0xC9, 0x95, 0x61, 0xDA, 0xA0, 0xBF, 0x6D, 0xE6,
  0x6E, 0x23, 0x47, 0x4E, 0x19, 0xE3, 0x38, 0x74, 0x27, 0xC1, 0xEA, 0xCE, 0x17, 0x68, 0x39, 0xA0,
  0xBF, 0x3C, 0xF9, 0x6F, 0xCA, 0xE3, 0x74, 0xBB, 0xC8, 0x6F, 0x43, 0x79, 0x8A, 0x60, 0xDE, 0xFB,
  0xE4, 0xA1, 0x03, 0xD6, 0xB7, 0x74, 0x0C, 0xCF, 0xF4, 0x40, 0xC6, 0xA3, 0x73, 0x5F, 0xD3, 0x2A,
  0x1E, 0xBC, 0xF6, 0xF6, 0xCC, 0x62, 0x4F, 0x38, 0xA0, 0x60, 0x65, 0x78, 0x34, 0x96, 0x60, 0x14,
  0xA4, 0x75, 0x13, 0x87, 0x0F, 0x70, 0x87, 0x96, 0x74, 0xA9, 0xF3, 0xE9, 0x50, 0xF2, 0x25, 0xBE,
  0x18, 0xBD, 0x59, 0xF3, 0x80, 0x6A, 0x15, 0xFB, 0xC2, 0xD1, 0x35, 0xBB, 0x39, 0xA9, 0x20, 0xC5,
  0x3D, 0xC9, 0x12, 0xBB, 0x30, 0x55, 0xE6, 0x47, 0x2F, 0x38, 0x0B, 0xDA, 0x36, 0xED, 0x05, 0xB1,
  0x9F, 0x27, 0xB7, 0xFA, 0x84, 0x42, 0x20, 0xDC, 0x45, 0x23, 0x38, 0x68, 0x6B, 0x1F, 0xF7, 0xAD,
  0x31, 0xC5, 0x2E, 0x05, 0x00, 0x36, 0x4C, 0x74, 0x29, 0x5C, 0x58, 0x60, 0xCE, 0x0E, 0xAE, 0x2E,
  0x51, 0xBD, 0xBA, 0x2A, 0x08, 0x71, 0xDA, 0x4E, 0x76, 0x29, 0xD1, 0x1C, 0x93, 0xC4, 0xB9, 0x05,
  0xEF, 0x4E, 0x2B, 0x0A, 0xC9, 0x1F, 0x9D, 0x16, 0xDD, 0xF3, 0xF9, 0x4A, 0xAE, 0xE5, 0xD6, 0x90,
  0xFC, 0xAA, 0xF3, 0xBF, 0xA0, 0xEB, 0xFD, 0x50, 0xB0, 0x22, 0xA2, 0x4D, 0x38, 0x82, 0x74, 0x94,
  0x4C, 0x2E, 0x3E, 0xC2, 0x1C, 0x8C, 0x05, 0x64, 0x6C, 0x73, 0x15, 0x3A, 0x8D, 0xF1, 0x77, 0x59,
  0xAE, 0xFC, 0xFB, 0x41, 0x01, 0xC0, 0xB8, 0x27, 0x9B, 0x38, 0xB3, 0x8F, 0x55, 0x77, 0x68, 0x15,
  0x91, 0x34, 0xEE, 0xDA, 0x4C, 0x82, 0x8B, 0xC6, 0xF4, 0x54, 0x9A, 0x73, 0xE6, 0xBF, 0xF1, 0x95
};
