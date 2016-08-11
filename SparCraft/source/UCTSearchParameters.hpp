#pragma once

#include "Common.h"

namespace SparCraft
{
    class UCTSearchParameters;

    namespace UCTMoveSelect
    {
        enum { HighestValue, MostVisited };
    }
}

class SparCraft::UCTSearchParameters
{											        // DEFAULT				DESCRIPTION
    PlayerID		    _maxPlayer;					    // Player_One			The player who will make maximizing moves
    PlayerID          _rootMoveSelection;             // MostVisited          Which node to pick from the root

	size_t		    _timeLimit;					    // 0					Search time limit. 0 means no time limit
    double          _cValue;                        // 1                    C constant for UCT formula
    size_t          _maxTraversals;                 // 100                  Max number of UCT traversals to make
    size_t          _maxChildren;                   // 10                   Max children at each node
    PlayerID          _moveOrdering;                  // ScriptFirst          Move ordering method for child generation
	PlayerID		    _evalMethod;				    // LTD				Evaluation function type
    PlayerID          _simScripts[2];                 // NOKDPS               Policy to use for playouts
	PlayerID		    _playerToMoveMethod;		    // Alternate			The player to move policy
	PlayerID		    _playerModel[2];                // None                 Player model to use for each player

    std::string     _graphVizFilename;              // ""                   File name to output graph viz file

    std::vector<PlayerID> _orderedMoveScripts;

    std::vector<std::vector<std::string> > _desc;    // 2-column description vector

public:

	// default constructor
	UCTSearchParameters() 
	    : _maxPlayer            (Players::Player_One)
        , _rootMoveSelection    (UCTMoveSelect::MostVisited)
	    , _timeLimit            (0)
        , _cValue               (1)
        , _maxTraversals        (100)
        , _maxChildren          (10)
        , _moveOrdering         (MoveOrderMethod::ScriptFirst)
        , _evalMethod           (SparCraft::EvaluationMethods::Playout)
	    , _playerToMoveMethod   (SparCraft::PlayerToMove::Alternate)
    {
	    setPlayerModel(Players::Player_One, PlayerModels::None);
	    setPlayerModel(Players::Player_Two, PlayerModels::None);
        setSimScripts(PlayerModels::NOKDPS, PlayerModels::NOKDPS);
    }

    const PlayerID & maxPlayer()							        const   { return _maxPlayer; }
    const size_t & timeLimit()							        const   { return _timeLimit; }
    const double & cValue()							            const   { return _cValue; }
    const size_t & maxTraversals()						        const   { return _maxTraversals; }
    const size_t & maxChildren()                                const   { return _maxChildren; }
    const PlayerID & moveOrderingMethod()                         const   { return _moveOrdering; }
    const PlayerID & evalMethod()						            const   { return _evalMethod; }
    const PlayerID & simScript(const PlayerID & player)             const   { return _simScripts[player]; }
    const PlayerID & playerToMoveMethod()				            const   { return _playerToMoveMethod; }
    const PlayerID & playerModel(const PlayerID & player)	        const   { return _playerModel[player]; }
    const PlayerID & rootMoveSelectionMethod()                    const   { return _rootMoveSelection; }
    const std::string & graphVizFilename()                      const   { return _graphVizFilename; }
    const std::vector<PlayerID> & getOrderedMoveScripts()         const   { return _orderedMoveScripts; }
	
    void setMaxPlayer(const PlayerID & player)					        { _maxPlayer = player; }
    void setTimeLimit(const size_t & timeLimit)					        { _timeLimit = timeLimit; }  
    void setCValue(const double & c)					                { _cValue = c; }
    void setMaxTraversals(const size_t & traversals)                    { _maxTraversals = traversals; }
    void setMaxChildren(const size_t & children)                        { _maxChildren = children; }
    void setMoveOrderingMethod(const size_t & method)                   { _moveOrdering = method; }
    void setEvalMethod(const PlayerID & eval)						        { _evalMethod = eval; }
    void setPlayerToMoveMethod(const PlayerID & method)				    { _playerToMoveMethod = method; }
    void setSimScripts(const PlayerID & p1, const PlayerID & p2)		    { _simScripts[0] = p1; _simScripts[1] = p2; }
    void setRootMoveSelectionMethod(const PlayerID & method)              { _rootMoveSelection = method; }
    void setGraphVizFilename(const std::string & filename)              { _graphVizFilename = filename; }
    void addOrderedMoveScript(const PlayerID & script)                    { _orderedMoveScripts.push_back(script); }
    void setPlayerModel(const PlayerID & player, const PlayerID & model)	{ _playerModel[player] = model; }	

    std::vector<std::vector<std::string> > & getDescription()
    {
        if (_desc.size() == 0)
        {
            _desc.push_back(std::vector<std::string>());
            _desc.push_back(std::vector<std::string>());

            std::stringstream ss;

            _desc[0].push_back("Player Type:");
            _desc[0].push_back("Time Limit:");
            _desc[0].push_back("C Value:");
            _desc[0].push_back("Max Traversals:");
            _desc[0].push_back("Max Children:");
            _desc[0].push_back("Move Ordering:");
            _desc[0].push_back("Player To Move:");
            _desc[0].push_back("Opponent Model:");

            ss << "UCT";                                                _desc[1].push_back(ss.str()); ss.str(std::string());
            ss << timeLimit() << "ms";                                  _desc[1].push_back(ss.str()); ss.str(std::string());
            ss << cValue();                                             _desc[1].push_back(ss.str()); ss.str(std::string());
            ss << maxTraversals();                                      _desc[1].push_back(ss.str()); ss.str(std::string());
            ss << maxChildren();                                        _desc[1].push_back(ss.str()); ss.str(std::string());
            //ss << MoveOrderMethod::getName(moveOrderingMethod());         _desc[1].push_back(ss.str()); ss.str(std::string());
            //ss << PlayerToMove::getName(playerToMoveMethod());            _desc[1].push_back(ss.str()); ss.str(std::string());
            //ss << PlayerModels::getName(playerModel((maxPlayer()+1)%2));  _desc[1].push_back(ss.str()); ss.str(std::string());
        }
        
        return _desc;
    }
};
