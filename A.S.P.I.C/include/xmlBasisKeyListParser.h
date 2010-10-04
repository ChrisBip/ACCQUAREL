#ifndef _XML_BASIS_KEY_LIST_PARSER_
#define _XML_BASIS_KEY_LIST_PARSER_

#include "aspicConfiguration.h"
#include <containor.h>
#include <xmlDocumentParser.h>

/**
 * Classe pour retrouver une liste de toutes les cl�s de base disponible sur 
 * la plate forme.
 */
class xmlBasisKeyListParser : public xmlDocumentParser
{
private:
	
	/**
	 * L'objet xmlBasisKeyListParser qui va vraiment tout faire.
	 */
	static xmlBasisKeyListParser * BasisKeyListParser;

protected:

	/**
	 * Constructeur par d�faut.
	 */
	inline xmlBasisKeyListParser(void)
	{
		;
	}

	/**
	 * Destructeur.
	 */
	inline virtual ~xmlBasisKeyListParser(void)
	{
		;
	}

	/**
	 * M�thode pour retrouver le sch�ma associ� au fichier XML que nous allons pars�.
	 */
	inline string getSchemaURI(void) const
	{
		return aspicConfiguration::getBasisKeyListSchemaPath();
	}


	/**
	 * M�thode pour retrouver dans l'objet la liste des cl�s pour les bases gaussiennes.
	 *
	 */
	inline const containor<string> getBasisList(void) const
	{
		containor<string> basisList;
		DOMNodeList * nodeBasisList;
		int nbrOfBasis , i;

		nodeBasisList = getElementsByTagName("BasisKey");
		
		if(nodeBasisList == NULL || (nbrOfBasis=nodeBasisList->getLength()) == 0) {
			basisList.clear();
			return basisList;
		} 
			
		basisList.setSizes(nbrOfBasis);

		for(i=0 ; i < nbrOfBasis ; i++) {
			basisList[i] = getNodeStringValue(nodeBasisList->item(i),xmlParser::Remove_White_Space);
		}

		return basisList;
	}

public:

	/**
	 * M�thode pour se connecter.
	 */
	inline static void connect(void) {
	
		if(connected()) {
			return;
		}
	
		BasisKeyListParser = new xmlBasisKeyListParser;
		BasisKeyListParser->load(aspicConfiguration::getBasisKeyListPath());
	}

	/**
	 * M�thode pour savoir si l'on est d�connect� ou pas.
	 *
	 * @return true lorsque l'on est connect�, false sinon.
	 */
	inline static bool connected(void)
	{
		if(BasisKeyListParser == NULL) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * M�thode pour se d�connecter.
	 */
	inline static void disconnect(void)
	{
		if(connected() == false) {
			return;
		} else {
			delete BasisKeyListParser;
			BasisKeyListParser = NULL;
		}
	}


	/**
	 * M�thode pour r�cup�rer la liste des bases gaussiennes pr�sentes :
	 *
	 * @return la liste de toutes les cl�s de base qui peuvent etre utilis�es
	 * sur la plate forme.
	 */
	static const containor<string> getBasisKeyList(void)
	{
		containor<string> basisKeyList;

		if(connected() == false) {
			connect();
		}	 
		
		basisKeyList = BasisKeyListParser->getBasisList();

		disconnect();
		return basisKeyList;
	}

};

#endif
