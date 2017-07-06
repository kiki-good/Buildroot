#! /bin/sh
/usr/bin/hciconfig hci0 up
check=$(/usr/bin/bccmd psread -s1 | /bin/grep "&22c0 = 0001" | /bin/wc -l)
if [ $check -eq "0" ]; then
        check_flash_formated=$(bccmd psread -s1| wc -l)
        if [ $check_flash_formated -eq "0" ]; then
                /bin/echo "###################################################################"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "# Bluetooth Adapter programming not supported on this CAD version #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "#                                                                 #"
                /bin/echo "###################################################################"
		cannot_pgm=1
        else
                /usr/bin/bccmd psload -s1 -r /etc/pskey_reduce_inquiry_priority_and_disable_deep_sleep.psr
        fi
else
        /usr/bin/hciconfig hci0 down
fi

/usr/bin/hciconfig hci0 up
check=$(/usr/bin/bccmd psread -s1 | /bin/grep "&2488 = 0001 0001 0001 0001 0001 0001 0001 0001 0001 0001 0001 0001 0001 0000 0000 0000 0001" | /bin/wc -l)
if [ $check -eq "0" ]; then
        check_flash_formated=$(bccmd psread -s1| wc -l)
        if [ $check_flash_formated -eq "0" ]; then
		echo "Cannot program Bluetooth coex transaction priority table!!"	
        else
                /usr/bin/bccmd psload -s1 -r /etc/pskey_coex_transaction_priority_table.psr
        fi
else
        /usr/bin/hciconfig hci0 down
fi
