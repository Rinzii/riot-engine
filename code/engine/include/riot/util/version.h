// Copyright WizWorks, Inc. All Rights Reserved.

#pragma once
#include <cstdint>
#include <string>

namespace riot
{
	///
	/// \brief Semantic Version
	///

	struct Version
	{
		std::uint32_t major{};
		std::uint32_t minor{};
		std::uint32_t patch{};

		bool operator<(const Version & other) const
		{
			if (major < other.major) return true;
			if (major > other.major) return false;
			if (minor < other.minor) return true;
			if (minor > other.minor) return false;
			return patch < other.patch;
		}

		bool operator>(const Version & other) const { return other < *this; }

		bool operator==(const Version & other) const { return major == other.major && minor == other.minor && patch == other.patch; }

		bool operator!=(const Version & other) const { return !(*this == other); }

		[[nodiscard]] constexpr std::uint32_t getVersion() const { return (major << 22U) | (minor << 12U) | (patch); }

		[[nodiscard]] std::string to_string() const { return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch); }
	};
} // namespace riot
