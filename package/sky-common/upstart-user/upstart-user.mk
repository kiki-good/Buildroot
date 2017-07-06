#############################################################
#
# upstart-user
#
#############################################################

UPSTART_USER_SCRIPT:=$(TARGET_DIR)/etc/upstart-user

upstart-user:
	@rm -f $(UPSTART_USER_SCRIPT)
	@touch $(UPSTART_USER_SCRIPT)
	@chmod a+x $(UPSTART_USER_SCRIPT)
	@echo "10002" >> $(UPSTART_USER_SCRIPT)

upstart-user-source:

upstart-user-clean:
	# Remove the script and create a new one
	rm -f $(UPSTART_USER_SCRIPT)

upstart-user-dirclean: upstart-user-clean


#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_UPSTART_USER),y)
TARGETS+=upstart-user
endif
