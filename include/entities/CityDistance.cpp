    CityDistance()

        CityDistance(std::string name, int id, std::string role):
            from_city_id(0), to_city_id(0), distance(0) {}

        //Getters
        int getToId() const
        {
            return to_city_id;
        }
        int getFromId() const
        {
            return from_city_id;
        }
        int getDistance() const
        {
            return distance;
        }

        //Setters
        void setToId(int i)
        {
            to_city_id = i;
        }
        void setFromId(int i)
        {
            from_city_id = i;
        }
        void setDistance(int i)
        {
            distance = i;
        }