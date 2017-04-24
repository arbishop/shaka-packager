// Copyright 2015 Google Inc. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef MEDIA_CODECS_VP_CODEC_CONFIGURATION_RECORD_H_
#define MEDIA_CODECS_VP_CODEC_CONFIGURATION_RECORD_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "packager/base/macros.h"
#include "packager/base/optional.h"
#include "packager/media/base/video_stream_info.h"

namespace shaka {
namespace media {

/// The below enums are from ffmpeg/libavutil/pixfmt.h.
/// Chromaticity coordinates of the source primaries.
enum AVColorPrimaries {
  AVCOL_PRI_RESERVED0 = 0,
  /// Also ITU-R BT1361 / IEC 61966-2-4 / SMPTE RP177 Annex B
  AVCOL_PRI_BT709 = 1,
  AVCOL_PRI_UNSPECIFIED = 2,
  AVCOL_PRI_RESERVED = 3,
  /// Also FCC Title 47 Code of Federal Regulations 73.682 (a)(20)
  AVCOL_PRI_BT470M = 4,
  /// Also ITU-R BT601-6 625 / ITU-R BT1358 625 / ITU-R BT1700 625 PAL & SECAM
  AVCOL_PRI_BT470BG = 5,
  /// Also ITU-R BT601-6 525 / ITU-R BT1358 525 / ITU-R BT1700 NTSC
  AVCOL_PRI_SMPTE170M = 6,
  /// Functionally identical to above
  AVCOL_PRI_SMPTE240M = 7,
  /// Colour filters using Illuminant C
  AVCOL_PRI_FILM = 8,
  /// ITU-R BT2020
  AVCOL_PRI_BT2020 = 9,
  /// SMPTE ST 428-1 (CIE 1931 XYZ)
  AVCOL_PRI_SMPTE428 = 10,
  AVCOL_PRI_SMPTEST428_1 = AVCOL_PRI_SMPTE428,
  /// SMPTE ST 431-2 (2011)
  AVCOL_PRI_SMPTE431 = 11,
  /// SMPTE ST 432-1 D65 (2010)
  AVCOL_PRI_SMPTE432 = 12,
  ///< Not part of ABI
  AVCOL_PRI_NB
};

/// Color Transfer Characteristic.
enum AVColorTransferCharacteristic {
  AVCOL_TRC_RESERVED0 = 0,
  /// Also ITU-R BT1361
  AVCOL_TRC_BT709 = 1,
  AVCOL_TRC_UNSPECIFIED = 2,
  AVCOL_TRC_RESERVED = 3,
  /// Also ITU-R BT470M / ITU-R BT1700 625 PAL & SECAM
  AVCOL_TRC_GAMMA22 = 4,
  /// Also ITU-R BT470BG
  AVCOL_TRC_GAMMA28 = 5,
  /// Also ITU-R BT601-6 525 or 625 / ITU-R BT1358 525 or 625 / ITU-R BT1700
  /// NTSC
  AVCOL_TRC_SMPTE170M = 6,
  AVCOL_TRC_SMPTE240M = 7,
  /// "Linear transfer characteristics"
  AVCOL_TRC_LINEAR = 8,
  /// "Logarithmic transfer characteristic (100:1 range)"
  AVCOL_TRC_LOG = 9,
  /// "Logarithmic transfer characteristic (100 * Sqrt(10) : 1 range)"
  AVCOL_TRC_LOG_SQRT = 10,
  /// IEC 61966-2-4
  AVCOL_TRC_IEC61966_2_4 = 11,
  /// ITU-R BT1361 Extended Colour Gamut
  AVCOL_TRC_BT1361_ECG = 12,
  /// IEC 61966-2-1 (sRGB or sYCC)
  AVCOL_TRC_IEC61966_2_1 = 13,
  /// ITU-R BT2020 for 10-bit system
  AVCOL_TRC_BT2020_10 = 14,
  /// ITU-R BT2020 for 12-bit system
  AVCOL_TRC_BT2020_12 = 15,
  /// SMPTE ST 2084 for 10-, 12-, 14- and 16-bit systems
  AVCOL_TRC_SMPTE2084 = 16,
  AVCOL_TRC_SMPTEST2084 = AVCOL_TRC_SMPTE2084,
  /// SMPTE ST 428-1
  AVCOL_TRC_SMPTE428 = 17,
  AVCOL_TRC_SMPTEST428_1 = AVCOL_TRC_SMPTE428,
  /// ARIB STD-B67, known as "Hybrid log-gamma"
  AVCOL_TRC_ARIB_STD_B67 = 18,
  /// Not part of ABI
  AVCOL_TRC_NB
};

/// YUV colorspace type (a.c.a matrix coefficients in 23001-8:2016).
enum AVColorSpace {
  /// Order of coefficients is actually GBR, also IEC 61966-2-1 (sRGB)
  AVCOL_SPC_RGB = 0,
  /// Also ITU-R BT1361 / IEC 61966-2-4 xvYCC709 / SMPTE RP177 Annex B
  AVCOL_SPC_BT709 = 1,
  AVCOL_SPC_UNSPECIFIED = 2,
  AVCOL_SPC_RESERVED = 3,
  /// FCC Title 47 Code of Federal Regulations 73.682 (a)(20)
  AVCOL_SPC_FCC = 4,
  /// Also ITU-R BT601-6 625 / ITU-R BT1358 625 / ITU-R BT1700 625 PAL & SECAM /
  /// IEC 61966-2-4 xvYCC601
  AVCOL_SPC_BT470BG = 5,
  /// Also ITU-R BT601-6 525 / ITU-R BT1358 525 / ITU-R BT1700 NTSC
  AVCOL_SPC_SMPTE170M = 6,
  /// Functionally identical to above
  AVCOL_SPC_SMPTE240M = 7,
  /// Used by Dirac / VC-2 and H.264 FRext, see ITU-T SG16
  AVCOL_SPC_YCOCG = 8,
  /// ITU-R BT2020 non-constant luminance system
  AVCOL_SPC_BT2020_NCL = 9,
  /// ITU-R BT2020 constant luminance system
  AVCOL_SPC_BT2020_CL = 10,
  /// SMPTE 2085, Y'D'zD'x
  AVCOL_SPC_SMPTE2085 = 11,
  /// Not part of ABI
  AVCOL_SPC_NB
};

/// Class for parsing or writing VP codec configuration record.
class VPCodecConfigurationRecord {
 public:
  enum ChromaSubsampling {
    CHROMA_420_VERTICAL = 0,
    CHROMA_420_COLLOCATED_WITH_LUMA = 1,
    CHROMA_422 = 2,
    CHROMA_444 = 3,
    CHROMA_440 = 4,
  };

  VPCodecConfigurationRecord();
  VPCodecConfigurationRecord(
      uint8_t profile,
      uint8_t level,
      uint8_t bit_depth,
      uint8_t chroma_subsampling,
      bool video_full_range_flag,
      uint8_t color_primaries,
      uint8_t transfer_characteristics,
      uint8_t matrix_coefficients,
      const std::vector<uint8_t>& codec_initialization_data);
  ~VPCodecConfigurationRecord();

  /// Parses input (in MP4 format) to extract VP codec configuration record.
  /// @return false if there is parsing errors.
  bool ParseMP4(const std::vector<uint8_t>& data);

  /// Parses input (in WebM format) to extract VP codec configuration record.
  /// @return false if there is parsing errors.
  bool ParseWebM(const std::vector<uint8_t>& data);

  /// @param data should not be null.
  /// Writes VP codec configuration record to buffer using MP4 format.
  void WriteMP4(std::vector<uint8_t>* data) const;

  /// @param data should not be null.
  /// Writes VP codec configuration record to buffer using WebM format.
  void WriteWebM(std::vector<uint8_t>* data) const;

  /// @return The codec string.
  std::string GetCodecString(Codec codec) const;

  // Merges the values from the given configuration.  If there are values in
  // both |*this| and |other|, the values in |other| take precedence.
  void MergeFrom(const VPCodecConfigurationRecord& other);

  void set_profile(uint8_t profile) { profile_ = profile; }
  void set_level(uint8_t level) { level_ = level; }
  void set_bit_depth(uint8_t bit_depth) { bit_depth_ = bit_depth; }
  void set_chroma_subsampling(uint8_t chroma_subsampling) {
    chroma_subsampling_ = chroma_subsampling;
  }
  void set_video_full_range_flag(bool video_full_range_flag) {
    video_full_range_flag_ = video_full_range_flag;
  }
  void set_color_primaries(uint8_t color_primaries) {
    color_primaries_ = color_primaries;
  }
  void set_transfer_characteristics(uint8_t transfer_characteristics) {
    transfer_characteristics_ = transfer_characteristics;
  }
  void set_matrix_coefficients(uint8_t matrix_coefficients) {
    matrix_coefficients_ = matrix_coefficients;
  }

  uint8_t profile() const { return profile_.value_or(0); }
  uint8_t level() const { return level_.value_or(10); }
  uint8_t bit_depth() const { return bit_depth_.value_or(8); }
  uint8_t chroma_subsampling() const {
    return chroma_subsampling_.value_or(CHROMA_420_COLLOCATED_WITH_LUMA);
  }
  bool video_full_range_flag() const {
    return video_full_range_flag_.value_or(false);
  }
  uint8_t color_primaries() const {
    return color_primaries_.value_or(AVCOL_PRI_UNSPECIFIED);
  }
  uint8_t transfer_characteristics() const {
    return transfer_characteristics_.value_or(AVCOL_TRC_UNSPECIFIED);
  }
  uint8_t matrix_coefficients() const {
    return matrix_coefficients_.value_or(AVCOL_SPC_UNSPECIFIED);
  }

 private:
  base::Optional<uint8_t> profile_;
  base::Optional<uint8_t> level_;
  base::Optional<uint8_t> bit_depth_;
  base::Optional<uint8_t> chroma_subsampling_;
  base::Optional<bool> video_full_range_flag_;
  base::Optional<uint8_t> color_primaries_;
  base::Optional<uint8_t> transfer_characteristics_;
  base::Optional<uint8_t> matrix_coefficients_;
  std::vector<uint8_t> codec_initialization_data_;

  // Not using DISALLOW_COPY_AND_ASSIGN here intentionally to allow the compiler
  // generated copy constructor and assignment operator. Since the internal data
  // is small, the performance impact is minimal.
};

}  // namespace media
}  // namespace shaka

#endif  // MEDIA_CODECS_VP_CODEC_CONFIGURATION_RECORD_H_
