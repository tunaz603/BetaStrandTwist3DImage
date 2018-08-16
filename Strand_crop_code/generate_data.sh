echo "find . -type f -regex '.*s.\\.pdb' | awk -F ':' '{cmd = \"cat \\\"\" \$1 \"\\\" | ./strand_crop KEY1 KEY2 > \\\"\" \$1\"_KEY3.pdb\\\"\"" > _gen_data_template
echo " print(cmd)" >> _gen_data_template
echo " system(cmd)" >> _gen_data_template
echo "}'" >> _gen_data_template

cp _gen_data_template _mod_data_template
rm _gen_data_template
sed -i -- 's/KEY1/'$1'/g' _mod_data_template
sed -i -- 's/KEY2/'$2'/g' _mod_data_template
sed -i -- 's/KEY3/'$3'/g' _mod_data_template
chmod +x _mod_data_template
cat _mod_data_template
./_mod_data_template
rm _mod_data_template
