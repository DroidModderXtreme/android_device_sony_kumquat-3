$(call inherit-product, device/sony/kumquat/full_kumquat.mk)

# Inherit Carbon common GSM stuff.
$(call inherit-product, vendor/carbon/config/common_gsm.mk)

# Inherit Carbon common Phone stuff.
$(call inherit-product, vendor/carbon/config/common_phone.mk)

PRODUCT_NAME := carbon_kumquat
PRODUCT_DEVICE := kumquat
