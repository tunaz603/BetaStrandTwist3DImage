find . -type f -regex '.*s.\.pdb_'$1'.pdb'

echo "Are you sure you want to delete the above? (enter 1 or 2)"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) find . -type f -regex '.*s.\.pdb_'$1'.pdb' -exec rm {} \; ; break;;
        No ) exit;;
    esac
done
